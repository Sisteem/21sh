/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tilde_expansion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagtab <ylagtab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 19:34:41 by ylagtab           #+#    #+#             */
/*   Updated: 2021/02/12 12:00:34 by ylagtab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "internal.h"

int		is_tilde(char *word, size_t i)
{
	return (word[i] == '~' && i == 0 &&
		(word[i + 1] == '\0' || word[i + 1] == '/' || ft_isspace(word[i + 1])));
}

char	*expand_tilde(char *word, char *result, size_t *end, size_t *start)
{
	char	*tilde;
	char	*str;

	tilde = env_get(g_shell_env, "HOME");
	if (tilde == NULL)
		tilde = ft_strdup("");
	str = ft_strsub(word, *start, *end - *start);
	str = ft_strjoin_free(result, str, 1, 1);
	str = ft_strjoin_free(str, tilde, 1, 0);
	*start = ++(*end);
	return (str);
}
