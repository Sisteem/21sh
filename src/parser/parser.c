/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagtab <ylagtab@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 18:41:42 by ylagtab           #+#    #+#             */
/*   Updated: 2021/03/03 15:54:19 by ylagtab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "internal.h"

t_vector	*parse_command(char *cmd)
{
	t_vector	*tokens;
	t_vector	*commands;

	tokens = tokenization(cmd);
	if (syntax_analys(tokens) == -1)
	{
		ft_vector_free(tokens, TRUE, del_token);
		return (NULL);
	}
	commands = construct_commands(tokens);
	free(tokens->array);
	free(tokens);
	return (commands);
}
