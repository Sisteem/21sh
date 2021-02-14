/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var_expansion.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagtab <ylagtab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 11:08:24 by ylagtab           #+#    #+#             */
/*   Updated: 2021/02/14 10:16:38 by ylagtab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "internal.h"

static char	*get_env_var(char *word, size_t *end)
{
	char	*var;
	char	*key;
	size_t	key_len;

	key_len = *end;
	while (word[key_len] && (ft_isalnum(word[key_len]) || word[key_len] == '_'))
		++key_len;
	key = ft_strsub(word, *end, key_len - *end);
	*end = key_len;
	var = env_get(g_shell_env, key);
	if (var == NULL)
		var = ft_strdup("");
	free(key);
	return (var);
}

int			is_env_var(char *word, size_t i)
{
	return (word[i] == '$' && (ft_isalpha(word[i + 1]) || word[i + 1] == '_'));
}

char		*expand_env_var(
				char *word, char *result, size_t *end, size_t *start)
{
	char	*var;
	char	*str;

	str = ft_strsub(word, *start, *end - *start);
	str = ft_strjoin_free(result, str, 1, 1);
	++(*end);
	var = get_env_var(word, end);
	str = ft_strjoin_free(str, var, 1, 1);
	*start = *end;
	return (str);
}
