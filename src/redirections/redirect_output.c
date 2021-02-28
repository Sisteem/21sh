/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_output.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagtab <ylagtab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 19:15:45 by ylagtab           #+#    #+#             */
/*   Updated: 2021/02/28 11:32:02 by ylagtab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "internal.h"

static void	check_output_file_errors(char *filename)
{
	struct stat st;

	g_errno = EUNK;
	stat(filename, &st);
	if (S_ISDIR(st.st_mode))
		g_errno = EPATHISDIR;
	else if (access(filename, W_OK) == -1)
		g_errno = EACCESS;
}

static int	open_file_for_write(char *filename, t_bool append)
{
	int	file_fd;
	int	write_mode;

	write_mode = O_WRONLY | O_CREAT | (append == TRUE ? O_APPEND : O_TRUNC);
	file_fd = open(filename, write_mode, UMASK);
	if (file_fd < 0)
		check_output_file_errors(filename);
	return (file_fd);
}

int			redirect_output(char *filename, int io_number, t_bool append)
{
	int	file_fd;

	file_fd = open_file_for_write(filename, append);
	if (file_fd < 0)
		return (-1);
	if (io_number == -1)
		io_number = STDOUT_FILENO;
	if (dup2(file_fd, io_number) == -1)
	{
		g_errno = EREDIRECTION;
		return (-1);
	}
	return (EXIT_SUCCESS);
}
