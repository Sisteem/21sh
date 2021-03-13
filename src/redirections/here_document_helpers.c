/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_document_helpers.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-idri <mel-idri@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/20 17:44:40 by ylagtab           #+#    #+#             */
/*   Updated: 2021/03/13 15:23:16 by mel-idri         ###   ########.fr       */
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

static int	read_buffer(char **buffer, char *delimiter, t_bool remove_tabs)
{
	char	*line;
	int		ret;

	while (1)
	{
		if ((ret = readline_21sh(&line, PS2)) == ERROR)
			exit(1);
		if (ret == EXIT)
			break ;
		if (ret == INTERRUPTED)
		{
			free(*buffer);
			return (EXIT_FAILURE);
		}
		if (remove_tabs)
			line = remove_leading_tabs(line);
		if (ft_strequ(line, delimiter))
		{
			free(line);
			break ;
		}
		*buffer = ft_strjoin_free(*buffer, line, 1, 1);
		*buffer = ft_strjoin_free(*buffer, "\n", 1, 0);
	}
	return (EXIT_SUCCESS);
}

void		free_delimiter(t_delimiter *delim)
{
	free(delim->str);
	free(delim);
}

int			get_redirect_fd(t_vector *tokens, size_t i)
{
	t_token		*tk;

	if (i > 0)
	{
		tk = (t_token*)tokens->array[i - 1]->content;
		if (tk->type == IO_NUMBER)
			return (*(int*)(tk->data));
	}
	return (STDIN_FILENO);
}

int			create_buffer_pipe(
	t_command *cmd, int fd, t_delimiter *delim, t_bool remove_tabs)
{
	char		*buffer;
	int			pipe_fds[2];
	t_here_doc	hd;

	if (pipe(pipe_fds) == -1)
	{
		g_errno = EUNK;
		ft_perror(NULL, NULL, FALSE);
		return (-1);
	}
	hd.fd = fd;
	hd.pipe_fd = pipe_fds[0];
	buffer = ft_strdup("");
	if (read_buffer(&buffer, delim->str, remove_tabs) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (!delim->is_quoted)
		buffer = expand_here_doc_buffer(buffer);
	ft_printf(pipe_fds[1], buffer);
	free(buffer);
	close(pipe_fds[1]);
	ft_vector_add(cmd->here_docs, &hd, sizeof(t_here_doc));
	return (EXIT_SUCCESS);
}
