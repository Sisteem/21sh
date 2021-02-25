/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_analys.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagtab <ylagtab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/02 13:24:24 by ylagtab           #+#    #+#             */
/*   Updated: 2021/02/25 11:46:09 by ylagtab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "internal.h"

static int	is_redirection(t_token_type type)
{
	return (type == DLESSDASH ||
		type == DLESS ||
		type == LESS ||
		type == ANDDGREAT ||
		type == ANDGREAT ||
		type == DGREAT ||
		type == GREATANDDASH ||
		type == GREATAND ||
		type == GREAT);
}

static int	handle_error(t_token_type token_type)
{
	static const char	*tokens_keys[] = {
		"",
		"`newline`",
		"`WORD`",
		"`;`",
		"`|`",
		"`IO_NUMBER`",
		"`>`",
		"`>>`",
		"`&>`",
		"`&>>`",
		"`<`",
		"`<<`",
		"`<<-`",
		"`>&`",
		"`>&-`"
	};

	g_errno = ESYNTAX;
	ft_perror(NULL, (char*)tokens_keys[token_type], FALSE);
	return (ESYNTAX);
}

int			syntax_analys(t_vector *tokens)
{
	size_t			i;
	t_token			*t;
	t_token_type	old_token_type;

	i = 0;
	old_token_type = NONE;
	while (i < tokens->length)
	{
		t = (t_token*)tokens->array[i]->content;
		if (t->type == PIPELINE)
			if (old_token_type == NONE || old_token_type == SEMI ||
				old_token_type == PIPELINE)
				return (handle_error(PIPELINE));
		if (t->type == SEMI)
			if (old_token_type == PIPELINE || is_redirection(old_token_type))
				return (handle_error(SEMI));
		if (is_redirection(old_token_type) && t->type != WORD)
			return (handle_error(t->type));
		if (i == tokens->length - 1)
			if (t->type == PIPELINE || is_redirection(t->type))
				return (handle_error(NEWLINE));
		old_token_type = t->type;
		++i;
	}
	return (EXIT_SUCCESS);
}
