/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagtab <ylagtab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 19:15:45 by ylagtab           #+#    #+#             */
/*   Updated: 2021/02/25 19:07:53 by ylagtab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "internal.h"

static void	check_input_file_errors(char *filename)
{
	struct stat st;

	g_errno = 0;
	if (stat(filename, &st) == -1)
		g_errno = EUNK;
	if (S_ISDIR(st.st_mode))
		g_errno = EPATHISDIR;
	else if (access(filename, F_OK) == -1)
		g_errno = ENOTFOUND;
	else if (access(filename, R_OK) == -1)
		g_errno = EACCESS;
}

static int	open_file_for_read(char *filename)
{
	int	file_fd;

	file_fd = open(filename, O_RDONLY, UMASK);
	check_input_file_errors(filename);
	return (file_fd);
}

void		redirect_input(char *filename, int io_number)
{
	int	file_fd;

	file_fd = open_file_for_read(filename);
	if (file_fd < 0)
		ft_perror(filename, NULL, FALSE);
	if (dup2(file_fd, io_number) == -1)
	{
		g_errno = EREDIRECTION;
		ft_perror(NULL, NULL, FALSE);
	}
}
