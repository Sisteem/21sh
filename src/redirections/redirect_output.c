/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_output.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagtab <ylagtab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 19:15:45 by ylagtab           #+#    #+#             */
/*   Updated: 2021/02/19 08:08:01 by ylagtab          ###   ########.fr       */
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

static int	open_file_for_write(char *filename, t_bool append)
{
	int	file_fd;
	int	write_mode;

	write_mode = O_WRONLY | O_APPEND;
	write_mode |= append == TRUE ? 0 : O_CREAT | O_TRUNC;
	file_fd = open(filename, write_mode, UMASK);
	check_output_file_errors(filename);
	return (file_fd);
}

void		redirect_output(char *filename, int io_number, t_bool append)
{
	int	file_fd;

	file_fd = open_file_for_write(filename, append);
	if (file_fd < 0)
		ft_perror(filename, NULL, TRUE);
	if (dup2(file_fd, io_number) == -1)
	{
		g_errno = EREDIRECTION;
		ft_perror(NULL, NULL, TRUE);
	}
}
