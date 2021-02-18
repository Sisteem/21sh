/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagtab <ylagtab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 19:05:36 by ylagtab           #+#    #+#             */
/*   Updated: 2021/02/18 19:06:29 by ylagtab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "internal.h"

static void	check_output_file_errors(char *filename)
{
	struct stat st;

	g_errno = 0;
	if (stat(filename, &st) == -1)
		g_errno = EUNK;
	if (S_ISDIR(st.st_mode))
		g_errno = EPATHISDIR;
	else if (access(filename, W_OK) == -1)
		g_errno = EACCESS;
}

int			open_file(t_redirect_input_info *redirect_input_info)
{
	int	file_fd;
	int	write_mode;

	write_mode = O_WRONLY | O_APPEND;
	write_mode |= redirect_input_info->append == TRUE ? 0 : O_CREAT | O_TRUNC;
	file_fd = open(redirect_input_info->file_pathname, write_mode, UMASK);
	check_output_file_errors(redirect_input_info->file_pathname);
	return (file_fd);
}
