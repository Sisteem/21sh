/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_fucntions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagtab <ylagtab@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 10:45:54 by ylagtab           #+#    #+#             */
/*   Updated: 2021/03/12 18:30:52 by ylagtab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one.h"

void	del_token(void *content, size_t content_size)
{
	t_token *token;

	(void)content_size;
	token = (t_token*)content;
	if (token->type == WORD || token->type == IO_NUMBER)
		free(token->data);
	free(content);
}

void	del_here_doc(void *content, size_t content_size)
{
	(void)content_size;
	free(content);
}

void	del_command(void *content, size_t content_size)
{
	t_command	*cmd;

	(void)content_size;
	cmd = (t_command*)content;
	ft_vector_free(cmd->here_docs, TRUE, del_here_doc);
	ft_vector_free(cmd->tokens, TRUE, del_token);
	free(content);
}

void	del_command_without_tokens(void *content, size_t content_size)
{
	t_command	*cmd;

	(void)content_size;
	cmd = (t_command*)content;
	ft_vector_free(cmd->here_docs, TRUE, del_here_doc);
	free(cmd->tokens->array);
	free(cmd->tokens);
	free(content);
}
