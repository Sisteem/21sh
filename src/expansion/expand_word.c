/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_word.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagtab <ylagtab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 11:34:03 by ylagtab           #+#    #+#             */
/*   Updated: 2021/02/13 11:38:04 by ylagtab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "internal.h"

static int	check_quote(char c, char *quote, size_t *end)
{
	char q;

	q = quote_type(c);
	if (q == BACK_SLASH && (*quote == 0 || *quote == DOUBLE_QUOTE))
		*end += 2;
	else if (*quote == 0 && quote_type(c) != 0)
	{
		*quote = c;
		++(*end);
	}
	else if (*quote == c)
	{
		*quote = 0;
		++(*end);
	}
	else
		return (0);
	return (1);
}

char		*expand_word(char *word)
{
	char	*result;
	size_t	end;
	size_t	start;
	char	quote;

	result = ft_strdup("");
	end = 0;
	start = 0;
	quote = 0;
	while (word[end])
	{
		if (check_quote(word[end], &quote, &end))
			continue ;
		if (is_tilde(word, end))
			result = expand_tilde(word, result, &end, &start);
		else if (quote != SINGLE_QUOTE && is_env_var(word, end))
			result = expand_env_var(word, result, &end, &start);
		if (word[end])
			++end;
	}
	result = ft_strjoin_free(result, ft_strsub(word, start, end - start), 1, 1);
	return (result);
}
