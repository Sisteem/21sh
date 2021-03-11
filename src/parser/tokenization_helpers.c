/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization_helpers.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagtab <ylagtab@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 09:37:15 by ylagtab           #+#    #+#             */
/*   Updated: 2021/03/11 18:37:48 by ylagtab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "internal.h"

static t_token_type	get_less_type(char **str)
{
	if (ft_strncmp(*str, "<<-", 3) == 0)
	{
		(*str) += 3;
		return (DLESSDASH);
	}
	if (ft_strncmp(*str, "<<", 2) == 0)
	{
		(*str) += 2;
		return (DLESS);
	}
	if (ft_strncmp(*str, "<&-", 3) == 0)
	{
		(*str) += 3;
		return (LESSANDDASH);
	}
	if (ft_strncmp(*str, "<&", 2) == 0)
	{
		(*str) += 2;
		return (LESSAND);
	}
	++(*str);
	return (LESS);
}

static void			skip_operator(char **str, t_token_type tk_type)
{
	if (tk_type == ANDDGREAT || tk_type == GREATANDDASH)
		(*str) += 3;
	else if (tk_type == ANDGREAT || tk_type == DGREAT || tk_type == GREATAND)
		(*str) += 2;
	else
		++(*str);
}

static t_token_type	get_great_type(char **str, t_tokenization *t)
{
	t_token_type tk_type;

	if (ft_strncmp(*str, "&>>", 3) == 0)
		tk_type = ANDDGREAT;
	else if (ft_strncmp(*str, "&>", 2) == 0)
		tk_type = ANDGREAT;
	else if (ft_strncmp(*str, ">>", 2) == 0)
		tk_type = DGREAT;
	else if (ft_strncmp(*str, ">&-", 3) == 0)
		tk_type = GREATANDDASH;
	else if (ft_strncmp(*str, ">&", 2) == 0)
		tk_type = GREATAND;
	else if (**str == '>')
		tk_type = GREAT;
	else
	{
		dynamic_str_push(t->token, **str);
		++(*str);
		return (WORD);
	}
	skip_operator(str, tk_type);
	return (tk_type);
}

t_token_type		fill_operator(char **str, t_tokenization *t)
{
	if (**str == ';')
	{
		++(*str);
		return (SEMI);
	}
	else if (**str == '|')
	{
		++(*str);
		return (PIPELINE);
	}
	if (**str == '<')
		return (get_less_type(str));
	if (**str == '>' || **str == '&')
		return (get_great_type(str, t));
	return (WORD);
}
