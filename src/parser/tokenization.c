/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagtab <ylagtab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/31 10:00:01 by ylagtab           #+#    #+#             */
/*   Updated: 2021/03/10 16:33:36 by ylagtab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "internal.h"

static t_token_type	fill_word(char **str, t_tokenization *t)
{
	char quote;
	char last_char;

	last_char = 0;
	while (**str && is_word(**str, t->quote))
	{
		quote = quote_type(**str);
		if (t->quote == SINGLE_QUOTE && quote == SINGLE_QUOTE)
			t->quote = 0;
		else if (t->quote == DOUBLE_QUOTE && quote == DOUBLE_QUOTE
			&& last_char != BACK_SLASH)
			t->quote = 0;
		else if (t->quote == BACK_SLASH)
			t->quote = 0;
		else if (t->quote == 0)
			t->quote = quote;
		last_char = **str;
		dynamic_str_push(t->token, **str);
		++(*str);
	}
	return (WORD);
}

static t_token_type	fill_number(char **str, t_tokenization *t)
{
	while (**str && is_number(**str, 0))
	{
		dynamic_str_push(t->token, **str);
		++(*str);
	}
	if (**str == '>' || **str == '<' ||
		(t->token_type == GREATAND && !is_word(**str, 0)))
		return (IO_NUMBER);
	return (WORD);
}

static void			add_token_to_list(t_tokenization *t)
{
	t_token	token;
	int		io_number;

	ft_bzero(&token, sizeof(t_token));
	token.type = t->token_type;
	if (t->token_type == WORD)
		t->token_type = NONE;
	if (token.type == WORD)
		token.data = ft_strsub(t->token->data, 0, t->token->length);
	else if (token.type == IO_NUMBER)
	{
		dynamic_str_push(t->token, '\0');
		io_number = ft_atoi(t->token->data);
		token.data = ft_malloc(sizeof(int));
		ft_memcpy(token.data, (void *)&io_number, sizeof(int));
	}
	t->token->length = 0;
	ft_vector_add(t->tokens_list, &token, sizeof(t_token));
}

t_vector			*tokenization(char *args_line)
{
	t_tokenization t;

	ft_bzero(&t, sizeof(t_tokenization));
	t.tokens_list = ft_vector_new();
	t.token = dynamic_str_new();
	while (*args_line)
	{
		if (is_number(*args_line, 0))
			if ((t.token_type = fill_number(&args_line, &t)) == IO_NUMBER)
				add_token_to_list(&t);
		if (is_operator(*args_line, 0))
			if ((t.token_type = fill_operator(&args_line, &t)) != WORD)
				add_token_to_list(&t);
		if (t.token_type == WORD || (*args_line && is_word(*args_line, 0)))
		{
			t.token_type = fill_word(&args_line, &t);
			add_token_to_list(&t);
		}
		while (ft_isspace(*args_line))
			++args_line;
	}
	dynamic_str_free(t.token);
	return (t.tokens_list);
}
