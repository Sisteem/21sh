/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_simple_command.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagtab <ylagtab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/14 17:12:34 by ylagtab           #+#    #+#             */
/*   Updated: 2021/02/18 12:33:51 by ylagtab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "internal.h"

static t_error	check_exec_pathname_errors(char *pathname, t_bool is_path)
{
	struct stat	st;

	if (is_path && ft_strlen(pathname) > PATH_MAX)
		return (ENAMETOOLONG);
	if (access(pathname, F_OK) == -1)
		return (ENOTFOUND);
	if (access(pathname, X_OK) == -1)
		return (EACCESS);
	if (lstat(pathname, &st) == -1)
		return (EUNK);
	if (S_ISDIR(st.st_mode))
		return (EPATHISDIR);
	return (0);
}

t_error			search_executable_in_path(char *cmd, char **pathname)
{
	char	*path_env_var;
	char	**path_dirs;
	t_error	pathname_error;
	t_error	err;

	if ((path_env_var = env_get(g_shell_env, "PATH")) == NULL)
		return (ENOTFOUND);
	path_dirs = ft_strsplit(path_env_var, ':');
	pathname_error = ENOTFOUND;
	*pathname = NULL;
	while (*path_dirs)
	{
		ft_strdel(pathname);
		*pathname = ft_strglue(*path_dirs, '/', cmd);
		err = check_exec_pathname_errors(*pathname, 0);
		if (err == 0)
			return (0);
		if (err != ENOTFOUND)
			pathname_error = err;
		++path_dirs;
	}
	return (pathname_error);
}

t_error			get_executable_pathname(t_token *cmd, char **pathname)
{
	t_error err;

	if (ft_strchr((char*)cmd->data, '/'))
	{
		if ((err = check_exec_pathname_errors((char*)cmd->data, 1)))
			return (err);
		*pathname = ft_strdup((char*)cmd->data);
		return (0);
	}
	return (search_executable_in_path(cmd->data, pathname));
}

void			exec_simple_command(t_vector *tokens)
{
	char *cmd;
	char **args;

	(void)args;
	perform_redirections(tokens);
	if (tokens->length == 0)
		return ;
	get_executable_pathname(tokens->array[0]->content, &cmd);
	print_tokens(tokens);
}
