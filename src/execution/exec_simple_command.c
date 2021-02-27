/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_simple_command.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagtab <ylagtab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/14 17:12:34 by ylagtab           #+#    #+#             */
/*   Updated: 2021/02/27 17:41:45 by ylagtab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "internal.h"

static t_error	check_exec_pathname_errors(char *pathname, t_bool is_path)
{
	struct stat	st;
	t_error		err;

	if (is_path && ft_strlen(pathname) > PATH_MAX)
		err = ENAMETOOLONG;
	else if (access(pathname, F_OK) == -1)
		err = is_path ? ENOTFOUND : ECMDNOTFOUND;
	else if (access(pathname, X_OK) == -1)
		err = EACCESS;
	else if (lstat(pathname, &st) == -1)
		err = EUNK;
	else if (S_ISDIR(st.st_mode))
		err = is_path ? EPATHISDIR : ECMDNOTFOUND;
	else
		err = EXIT_SUCCESS;
	if (err != ECMDNOTFOUND)
		g_errno = err;
	return (err);
}

char			*search_executable_in_path(char *cmd)
{
	char	*exe_path;
	char	*path_env_var;
	char	**path_dirs;

	g_errno = ECMDNOTFOUND;
	if ((path_env_var = env_get("PATH")) == NULL)
		return (NULL);
	path_dirs = ft_strsplit(path_env_var, ':');
	exe_path = NULL;
	while (*path_dirs)
	{
		exe_path = ft_strglue(*path_dirs, '/', cmd);
		if (check_exec_pathname_errors(exe_path, 0) == EXIT_SUCCESS)
		{
			g_errno = 0;
			return (exe_path);
		}
		ft_strdel(&exe_path);
		++path_dirs;
	}
	return (NULL);
}

char			*get_executable_pathname(t_token *cmd)
{
	if (ft_strchr((char*)cmd->data, '/'))
	{
		if (check_exec_pathname_errors((char*)cmd->data, 1) != EXIT_SUCCESS)
		{
			ft_perror(cmd->data, NULL, FALSE);
			return (NULL);
		}
		return (ft_strdup((char*)cmd->data));
	}
	return (search_executable_in_path(cmd->data));
}

static char		**tokens_to_strings_array(t_vector *tokens)
{
	t_token	*tk;
	char	**array;
	size_t	i;

	i = 0;
	array = (char**)ft_malloc((tokens->length + 1) * sizeof(char*));
	array[tokens->length] = NULL;
	while (i < tokens->length)
	{
		tk = (t_token*)tokens->array[i]->content;
		array[i] = (char*)tk->data;
		++i;
	}
	return (array);
}

int				exec_simple_command(t_vector *tokens, t_bool run_in_child)
{
	char	*exe_path;
	char	**args;
	char	**envp;
	int		exit_status;

	remove_quotes(tokens);
	if (perform_redirections(tokens) == -1)
		return (g_errno);
	if (tokens->length == 0)
		return (EXIT_SUCCESS);
	args = tokens_to_strings_array(tokens);
	if (is_built_in(args[0]))
		return (run_built_in(args, ft_strings_array_length(args + 1)));
	exe_path = get_executable_pathname(tokens->array[0]->content);
	if (exe_path == NULL)
		return (g_errno);
	envp = shell_env_to_envp(g_shell_env);
	if (run_in_child == FALSE || fork() == 0)
	{
		execve(exe_path, args, envp);
		return (EUNK);
	}
	else
		wait(&exit_status);
	return (exit_status);
}
