/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_executable_pathname.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagtab <ylagtab@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/28 09:27:58 by ylagtab           #+#    #+#             */
/*   Updated: 2021/03/02 10:43:05 by ylagtab          ###   ########.fr       */
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
	char	**path_dirs_tmp;

	g_errno = ECMDNOTFOUND;
	if ((path_env_var = env_get("PATH")) == NULL)
		return (NULL);
	path_dirs = ft_strsplit(path_env_var, ':');
	path_dirs_tmp = path_dirs;
	exe_path = NULL;
	while (*path_dirs)
	{
		exe_path = ft_strglue(*path_dirs, '/', cmd);
		if (check_exec_pathname_errors(exe_path, 0) == EXIT_SUCCESS)
		{
			g_errno = 0;
			break ;
		}
		ft_strdel(&exe_path);
		++path_dirs;
	}
	ft_free_strings_array(path_dirs_tmp);
	free(path_env_var);
	return (exe_path);
}

char			*get_executable_pathname(char *str)
{
	char *exe_path;

	if (ft_strchr(str, '/'))
	{
		if (check_exec_pathname_errors(str, 1) != EXIT_SUCCESS)
		{
			ft_perror(str, NULL, FALSE);
			return (NULL);
		}
		return (ft_strdup(str));
	}
	exe_path = search_executable_in_path(str);
	if (exe_path == NULL)
		ft_perror(str, NULL, FALSE);
	return (exe_path);
}
