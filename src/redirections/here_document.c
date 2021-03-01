/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_document.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagtab <ylagtab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/20 17:44:40 by ylagtab           #+#    #+#             */
/*   Updated: 2021/03/01 09:48:29 by ylagtab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "internal.h"

static char	*remove_leading_tabs(char *str)
{
	char	*result;
	size_t	i;

	if (str == NULL)
		return (NULL);
	i = 0;
	while (str[i])
	{
		if (str[i] != '\t')
			break ;
		++i;
	}
	result = ft_strdup(str + i);
	free(str);
	return (result);
}

static char	*read_buffer(char *delimiter, t_bool remove_tabs)
{
	char	*line;
	char	*buf;

	buf = ft_strdup("");
	while (1)
	{
		ft_printf(1, "> ");
		if (get_next_line(0, &line) == -1)
			return (buf);
		if (remove_tabs)
			line = remove_leading_tabs(line);
		if (line && ft_strcmp(line, delimiter) != 0)
		{
			buf = ft_strjoin_free(buf, line, 1, 1);
			buf = ft_strjoin_free(buf, "\n", 1, 0);
		}
		else
			return (buf);
	}
}

void		here_document(int fd, char *delimeter, t_bool remove_tabs)
{
	int pipe_fd[2];

	if (fd == -1)
		fd = STDIN_FILENO;
	if (pipe(pipe_fd) == -1)
	{
		g_errno = EUNK;
		ft_perror(NULL, NULL, TRUE);
	}
	ft_printf(pipe_fd[1], read_buffer(delimeter, remove_tabs));
	close(pipe_fd[1]);
	if (dup2(pipe_fd[0], fd) == -1)
	{
		g_errno = EREDIRECTION;
		ft_perror(NULL, NULL, TRUE);
	}
}
