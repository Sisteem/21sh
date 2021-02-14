/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagtab <ylagtab@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/22 00:24:35 by vanderwolk        #+#    #+#             */
/*   Updated: 2021/02/09 17:29:23 by ylagtab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one.h"

static void		show_error_msg(char *path, t_error err)
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
}

static t_error	handle_errors(char *path)
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

static t_error	change_dir(t_vector *mini_env, char *path)
{
	char	cwd[PATH_MAX];
	char	*current_dir;
	char	*dir_path;
	t_error	err;

	getcwd(cwd, PATH_MAX);
	if ((current_dir = env_get(mini_env, "PWD")) == NULL)
		current_dir = ft_strdup(cwd);
	if (path[0] == '/')
		dir_path = ft_strdup(path);
	else
		dir_path = join_paths(current_dir, path);
	if (chdir(dir_path) == 0)
	{
		env_remove(mini_env, "PWD");
		env_remove(mini_env, "OLDPWD");
		env_add(mini_env, "OLDPWD", current_dir);
		env_add(mini_env, "PWD", dir_path);
		err = 0;
	}
	else
		err = handle_errors(dir_path);
	free(current_dir);
	free(dir_path);
	return (err);
}

void			cd(t_vector *mini_env, char **args, size_t args_len)
{
	char	*path;
	t_error	err;

	if (args_len > 2)
	{
		ft_printf(2, "minishell: cd: to many arguments\n");
		return ;
	}
	err = 0;
	path = ft_strdup(args[1]);
	if (path == NULL)
		if ((path = env_get(mini_env, "HOME")) == NULL)
			err = ENOHOME;
	if (ft_strcmp(path, "-") == 0)
		if ((path = env_get(mini_env, "OLDPWD")) == NULL)
			err = ENOOLPPWD;
	if (ft_strlen(path) >= PATH_MAX)
		err = ENAMETOOLONG;
	if (err == 0)
		err = change_dir(mini_env, path);
	if (err)
		show_error_msg(path, err);
	free(path);
}
