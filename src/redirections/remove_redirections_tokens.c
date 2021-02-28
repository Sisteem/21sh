/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_redirections_tokens.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagtab <ylagtab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 19:06:48 by ylagtab           #+#    #+#             */
/*   Updated: 2021/02/28 11:30:18 by ylagtab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "internal.h"

static void	delete_token(void *content, size_t content_size)
{
	t_token *token;

	(void)content_size;
	token = (t_token*)content;
	if (token->type == WORD || token->type == IO_NUMBER)
		free(token->data);
	free(content);
}

void		remove_redirections_tokens(t_vector *tokens)
{
	t_token_type	tk_type;
	size_t			i;

	i = 0;
	while (i < tokens->length)
	{
		tk_type = ((t_token*)tokens->array[i]->content)->type;
		if (tk_type > PIPELINE)
		{
			ft_vector_remove_at(tokens, i, delete_token);
			if (tk_type != IO_NUMBER && tk_type != GREATANDDASH)
				ft_vector_remove_at(tokens, i, delete_token);
		}
		else
			++i;
	}
}
