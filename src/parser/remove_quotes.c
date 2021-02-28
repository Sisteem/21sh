/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagtab <ylagtab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/27 17:03:24 by ylagtab           #+#    #+#             */
/*   Updated: 2021/02/28 09:39:36 by ylagtab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "internal.h"

static int	is_quote(char c)
{
	if (c == DOUBLE_QUOTE || c == SINGLE_QUOTE)
		return (c);
	return (0);
}

void		fill_str(char **word, t_remove_quotes *rq)
{
	rq->backslash = !rq->backslash && **word == BACK_SLASH &&
			rq->quote != SINGLE_QUOTE;
	if (rq->backslash == FALSE)
	{
		rq->str[rq->s_index] = **word;
		++(rq->s_index);
	}
	++(*word);
}

static char	*remove_quotes_from_word(char *word)
{
	t_remove_quotes rq;

	ft_bzero(&rq, sizeof(t_remove_quotes));
	while (*word)
	{
		rq.quote = is_quote(*word);
		if (rq.quote)
		{
			++word;
			while (*word != rq.quote || rq.backslash)
				fill_str(&word, &rq);
			++word;
		}
		else
			while (*word && (!is_quote(*word) || rq.backslash))
				fill_str(&word, &rq);
	}
	return (ft_strsub(rq.str, 0, rq.s_index));
}

void		remove_quotes(t_vector *tokens)
{
	t_token	*token;
	char	*word;
	size_t	i;

	i = 0;
	while (i < tokens->length)
	{
		token = (t_token*)tokens->array[i]->content;
		if (token->type == WORD)
		{
			word = remove_quotes_from_word(token->data);
			free(token->data);
			token->data = word;
		}
		++i;
	}
}
