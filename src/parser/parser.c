/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagtab <ylagtab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 18:41:42 by ylagtab           #+#    #+#             */
/*   Updated: 2021/02/28 11:11:33 by ylagtab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "internal.h"

t_vector	*parse_command(char *cmd)
{
	t_vector	*tokens;
	t_vector	*commands;

	tokens = tokenization(cmd);
	if (syntax_analys(tokens) == -1)
		return (NULL);
	commands = construct_commands(tokens);
	return (commands);
}
