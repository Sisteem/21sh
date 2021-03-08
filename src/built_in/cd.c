/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagtab <ylagtab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/22 00:24:35 by vanderwolk        #+#    #+#             */
/*   Updated: 2021/03/08 12:43:00 by ylagtab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one.h"

static t_error		show_error_msg(char *path, t_error err)
{
	if (err == ENOHOME)
		ft_printf(2, "minisell: cd: HOME not set\n");
	else if (err == ENOOLPPWD)
		ft_printf(2, "minisell: cd: OLDPWD not set\n");
	else if (err == EACCESS)
		ft_printf(2, "minisell: cd: %s: Acess denied\n", path);
	else if (err == ENOTFOUND)
		ft_printf(2, "minisell: cd: %s: No such file or directory\n", path);
	else if (err == ENOTDIR)
		ft_printf(2, "minisell: cd: %s: Not a directory\n", path);
	else if (err == ENAMETOOLONG)
		ft_printf(2, "minisell: cd: %s: File name too long\n", path);
	else
		ft_printf(2, "minisell: cd: %s: An error has occured\n", path);
	return (err);
}

static t_error		handle_errors(char *path)
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
		return (EUNK);
	if (access(path, F_OK) == -1)
		return (ENOTFOUND);
	if (access(path, R_OK) == -1)
		return (EACCESS);
	if (S_ISDIR(st.st_mode))
		return (0);
	return (ENOTDIR);
}

static t_error		change_dir(char *path)
{
	char	*current_dir;
	char	*dir_path;
	t_error	err;

	if ((current_dir = env_get("PWD")) == NULL)
		current_dir = getcwd(NULL, PATH_MAX);
	if (current_dir == NULL)
		return (EUNK);
	dir_path = path[0] == '/' ? ft_strdup(path) : join_paths(current_dir, path);
	if (chdir(dir_path) == 0)
	{
		env_remove("PWD");
		env_remove("OLDPWD");
		env_add("OLDPWD", current_dir);
		env_add("PWD", dir_path);
		err = 0;
	}
	else
		err = handle_errors(dir_path);
	free(current_dir);
	free(dir_path);
	return (err);
}

int					cd(char **args, size_t args_len)
{
	char	*path;
	t_error	err;

	if (args_len > 1)
	{
		ft_printf(2, "minishell: cd: to many arguments\n");
		return (1);
	}
	err = 0;
	path = ft_strdup(args[0]);
	if (path == NULL)
		if ((path = env_get("HOME")) == NULL)
			err = ENOHOME;
	if (ft_strequ(path, "-"))
		if ((path = env_get("OLDPWD")) == NULL)
			err = ENOOLPPWD;
	if (ft_strlen(path) >= PATH_MAX)
		err = ENAMETOOLONG;
	if (err == 0)
		err = change_dir(path);
	if (err)
		show_error_msg(path, err);
	free(path);
	return (err);
}
