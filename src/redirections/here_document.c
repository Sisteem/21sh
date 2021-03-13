/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_document.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagtab <ylagtab@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 17:21:48 by ylagtab           #+#    #+#             */
/*   Updated: 2021/03/13 11:02:42 by ylagtab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "internal.h"

static t_bool	is_quoted(char *str)
{
	while (*str)
	{
		if (quote_type(*str) > 0)
			return (TRUE);
		++str;
	}
	return (FALSE);
}

t_delimiter		*get_delimiter(t_token *tk)
{
	t_delimiter	*delim;

	delim = (t_delimiter*)ft_malloc(sizeof(t_delimiter));
	delim->str = tk->data;
	delim->is_quoted = is_quoted(delim->str);
	delim->str = remove_quotes_from_word(delim->str);
	return (delim);
}

int				prepare_cmd_here_docs(t_command *cmd)
{
	t_token		*tk;
	t_delimiter	*delim;
	size_t		i;
	int			fd;
	int			err;

	i = 0;
	while (i < cmd->tokens->length)
	{
		tk = (t_token*)cmd->tokens->array[i]->content;
		if (tk->type == DLESSDASH || tk->type == DLESS)
		{
			fd = get_redirect_fd(cmd->tokens, i);
			delim = get_delimiter(cmd->tokens->array[i + 1]->content);
			err = create_buffer_pipe(cmd, fd, delim, tk->type == DLESSDASH);
			free_delimiter(delim);
			if (err == EXIT_FAILURE)
				return (EXIT_FAILURE);
		}
		++i;
	}
	return (EXIT_SUCCESS);
}

int				prepare_commands_here_docs(t_vector *commands)
{
	t_command	*cmd;
	size_t		i;

	i = 0;
	while (i < commands->length)
	{
		cmd = (t_command*)commands->array[i]->content;
		if (cmd->type == PIPE_SEQ)
			continue ;
		if (prepare_cmd_here_docs(cmd) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		++i;
	}
	return (EXIT_SUCCESS);
}

int				here_document(t_vector *here_docs, int index)
{
	t_here_doc	*hd;

	hd = (t_here_doc*)here_docs->array[index]->content;
	if (dup2(hd->pipe_fd, hd->fd) == -1)
	{
		g_errno = EREDIRECTION;
		return (-1);
	}
	return (EXIT_SUCCESS);
}
