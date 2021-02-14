/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagtab <ylagtab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/18 19:02:46 by ylagtab           #+#    #+#             */
/*   Updated: 2021/02/12 10:03:11 by ylagtab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "internal.h"

char	quote_type(char c)
{
	if (c == DOUBLE_QUOTE || c == SINGLE_QUOTE || c == BACK_SLASH)
		return (c);
	return (0);
}

int		is_space(char c, int quote)
{
	return (ft_isspace(c) && !quote);
}

int		is_number(char c, int quote)
{
	return (ft_isdigit(c) && !quote);
}

int		is_operator(char c, int quote)
{
	return (!quote && (
		c == ';' || c == '|' || c == '>' || c == '<' || c == '&'));
}

int		is_word(char c, int quote)
{
	return (
		!is_space(c, quote) &&
		!is_operator(c, quote));
}
