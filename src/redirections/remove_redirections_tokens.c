/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_redirections_tokens.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagtab <ylagtab@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 19:06:48 by ylagtab           #+#    #+#             */
/*   Updated: 2021/03/02 20:22:03 by ylagtab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "internal.h"

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
			ft_vector_remove_at(tokens, i, del_token);
			if (tk_type != IO_NUMBER && tk_type != GREATANDDASH)
				ft_vector_remove_at(tokens, i, del_token);
		}
		else
			++i;
	}
}
