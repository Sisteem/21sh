/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_to_fileds.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagtab <ylagtab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/13 17:34:20 by ylagtab           #+#    #+#             */
/*   Updated: 2021/02/20 16:25:08 by ylagtab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "internal.h"

static char		set_quote(char c, char old_quote, char last_char)
{
	char quote;

	quote = quote_type(c);
	if (old_quote == SINGLE_QUOTE && quote == SINGLE_QUOTE)
		return (0);
	else if (old_quote == DOUBLE_QUOTE && quote == DOUBLE_QUOTE
		&& last_char != BACK_SLASH)
		return (0);
	else if (old_quote == BACK_SLASH)
		return (0);
	else if (old_quote == 0)
		return (quote);
	return (old_quote);
}

static char		*get_word(char *str, size_t *i)
{
	char	word[4096];
	size_t	w_index;
	char	quote;
	char	last_char;

	quote = 0;
	last_char = 0;
	w_index = 0;
	while (str[*i] && !is_space(str[*i], quote))
	{
		quote = set_quote(str[*i], quote, last_char);
		word[w_index] = str[*i];
		last_char = str[*i];
		++(*i);
		++(w_index);
	}
	return (ft_strsub(word, 0, w_index));
}

static void	split_words(t_vector *words, char *str)
{
	char		*word;
	size_t		i;

	i = 0;
	ft_vector_init(words);
	while (str[i])
	{
		while (ft_isspace(str[i]))
			i++;
		if (str[i])
		{
			word = get_word(str, &i);
			ft_vector_add(words, &word, sizeof(char*));
		}
	}
}

static void	token_del(void *content, size_t content_size)
{
	(void)content_size;
	free(content);
}

void	tokens_to_fileds(t_vector *tokens, size_t *index)
{
	t_token		tk;
	t_vector	words;

	tk = *(t_token*)tokens->array[*index]->content;
	split_words(&words, tk.data);
	if (words.length > 1)
	{
		ft_vector_remove_at(tokens, *index, token_del);
		while (words.length > 0)
		{
			tk.data = *((char**)words.array[words.length - 1]->content);
			tk.type = WORD;
			ft_vector_add_at(tokens, *index, &tk, sizeof(t_token));
			free(words.array[words.length - 1]);
			--(words.length);
		}
	}
	free(words.array);
}
