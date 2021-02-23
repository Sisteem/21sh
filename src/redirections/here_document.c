/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_document.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagtab <ylagtab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/20 17:44:40 by ylagtab           #+#    #+#             */
/*   Updated: 2021/02/21 09:27:04 by ylagtab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "internal.h"

static void	read_input(int fd, char *delimiter)
{
	char	*line;

	while (get_next_line(0, &line) != -1)
	{
		if (line == NULL)
			return ;
		if (ft_strcmp(line, delimiter) != 0)
			ft_printf(fd, "%s", line);
		else
			return ;
	}
}

void		here_document(int fd, char *delimeter)
{
	int pipe_fd[2];

	if (pipe(pipe_fd) == -1)
	{
		g_errno = EUNK;
		ft_perror(NULL, NULL, TRUE);
	}
	if (fork() == 0)
	{
		close(pipe_fd[0]);
		read_input(pipe_fd[1], delimeter);
		return ;
	}
	close(pipe_fd[1]);
	if (dup2(pipe_fd[0], fd) == -1)
	{
		g_errno = EREDIRECTION;
		ft_perror(NULL, NULL, TRUE);
	}
}
