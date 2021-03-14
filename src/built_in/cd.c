/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagtab <ylagtab@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/22 00:24:35 by vanderwolk        #+#    #+#             */
/*   Updated: 2021/03/14 08:33:16 by ylagtab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one.h"

static void			show_error_msg(char *path)
{
	char *error_prefix;

	error_prefix = ft_strdup("cd");
	if (g_errno != ENOHOME && g_errno != ENOOLPPWD)
	{
		error_prefix = ft_strjoin_free(error_prefix, ": ", 1, 0);
		error_prefix = ft_strjoin_free(error_prefix, path, 1, 0);
	}
	ft_perror(error_prefix, NULL, FALSE);
	free(error_prefix);
}

static void			handle_errors(char *path)
{
	struct stat	st;
	int			err;

	err = 0;
	ft_bzero(&st, sizeof(struct stat));
	if (lstat(path, &st) == -1)
		err = 1;
	if (stat(path, &st) == -1)
		err = 1;
	if (S_ISLNK(st.st_mode) && err == 1)
		g_errno = EUNK;
	else if (access(path, F_OK) == -1)
		g_errno = ENOTFOUND;
	else if (access(path, R_OK) == -1)
		g_errno = EACCESS;
	else if (S_ISDIR(st.st_mode))
		g_errno = EXIT_SUCCESS;
	else
		g_errno = ENOTDIR;
}

static void			change_dir(char *path)
{
	char	*current_dir;
	char	*dir_path;

	if ((current_dir = env_get("PWD")) == NULL)
		if ((current_dir = getcwd(NULL, PATH_MAX)) == NULL)
		{
			g_errno = EUNK;
			return ;
		}
	dir_path = path[0] == '/' ? ft_strdup(path) : join_paths(current_dir, path);
	if (chdir(dir_path) == 0)
	{
		env_remove("PWD");
		env_remove("OLDPWD");
		env_add("OLDPWD", current_dir);
		env_add("PWD", dir_path);
		g_errno = 0;
	}
	else
		handle_errors(dir_path);
	free(current_dir);
	free(dir_path);
}

static char			*get_path(char *str)
{
	char *path;

	path = NULL;
	if (str == NULL)
		if ((path = env_get("HOME")) == NULL)
			g_errno = ENOHOME;
	if (ft_strequ(str, "-"))
		if ((path = env_get("OLDPWD")) == NULL)
			g_errno = ENOOLPPWD;
	if (path == NULL)
		path = ft_strdup(str);
	return (path);
}

int					cd(char **args, size_t args_len)
{
	char	*path;

	g_errno = EXIT_SUCCESS;
	if (args_len > 1)
	{
		ft_printf(2, "21sh: cd: to many arguments\n");
		return (EUNK);
	}
	path = get_path(args[0]);
	if (ft_strlen(path) >= PATH_MAX)
		g_errno = ENAMETOOLONG;
	if (g_errno == 0)
		change_dir(path);
	if (g_errno)
		show_error_msg(path);
	free(path);
	return (g_errno);
}
