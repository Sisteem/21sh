/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagtab <ylagtab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 18:41:42 by ylagtab           #+#    #+#             */
/*   Updated: 2021/02/25 11:46:06 by ylagtab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "internal.h"

void		print_commands(t_vector *commands)
{
	static char	*types[] = {"", "simple command", "pipeline sequence"};
	t_command	*cmd;
	size_t		i;

	i = 0;
	while (i < commands->length)
	{
		cmd = commands->array[i]->content;
		if (cmd->tokens)
			ft_printf(1, "%s\n", types[cmd->type]);
		print_tokens(cmd->tokens);
		ft_printf(1, "--------------------------------\n");
		i++;
	}
}

t_vector	*parse_command(char *cmd)
{
	t_vector	*tokens;
	t_vector	*commands;

	tokens = tokenization(cmd);
	if (syntax_analys(tokens) != EXIT_SUCCESS)
		return (NULL);
	commands = construct_commands(tokens);
	return (commands);
}
