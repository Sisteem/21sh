/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_simple_command.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagtab <ylagtab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/14 17:12:34 by ylagtab           #+#    #+#             */
/*   Updated: 2021/02/25 17:35:30 by ylagtab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "internal.h"

static t_error	check_exec_pathname_errors(char *pathname, t_bool is_path)
{
	struct stat	st;

	if (is_path && ft_strlen(pathname) > PATH_MAX)
		return (ENAMETOOLONG);
	if (access(pathname, F_OK) == -1)
		return (is_path ? ENOTFOUND : ECMDNOTFOUND);
	if (access(pathname, X_OK) == -1)
		return (EACCESS);
	if (lstat(pathname, &st) == -1)
		return (EUNK);
	if (S_ISDIR(st.st_mode))
		return (EPATHISDIR);
	return (0);
}

char			*search_executable_in_path(char *cmd)
{
	char	*exe_path;
	char	*path_env_var;
	char	**path_dirs;
	t_error	err;

	g_errno = ECMDNOTFOUND;
	if ((path_env_var = env_get("PATH")) == NULL)
		return (NULL);
	path_dirs = ft_strsplit(path_env_var, ':');
	exe_path = NULL;
	while (*path_dirs)
	{
		exe_path = ft_strglue(*path_dirs, '/', cmd);
		err = check_exec_pathname_errors(exe_path, 0);
		if (err == 0)
		{
			g_errno = 0;
			return (exe_path);
		}
		if (err != ECMDNOTFOUND)
			g_errno = err;
		ft_strdel(&exe_path);
		++path_dirs;
	}
	return (NULL);
}

char			*get_executable_pathname(t_token *cmd)
{
	if (ft_strchr((char*)cmd->data, '/'))
	{
		if ((g_errno = check_exec_pathname_errors((char*)cmd->data, 1)))
			return (NULL);
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

int			exec_simple_command(t_vector *tokens, t_bool run_in_child)
{
	char *exe_path;
	char **args;
	char **envp;
	int		exit_status;

	perform_redirections(tokens);
	if (tokens->length == 0)
		return (1);
	args = tokens_to_strings_array(tokens);
	if (is_built_in(args[0]))
		return (run_built_in(args, ft_strings_array_length(args + 1)));
	exe_path = get_executable_pathname(tokens->array[0]->content);
	if (exe_path == NULL)
		ft_perror(((t_token*)tokens->array[0]->content)->data, NULL, TRUE);
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
