/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   construct_commands.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagtab <ylagtab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 21:47:26 by ylagtab           #+#    #+#             */
/*   Updated: 2021/03/04 12:07:11 by ylagtab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "internal.h"

static void	add_command(t_vector *tokens, t_construct_commands *c)
{
	t_command	cmd;

	cmd.type = c->cmd_type;
	cmd.tokens = ft_vector_new_capacity(c->i - c->j);
	while (c->j < c->i)
	{
		cmd.tokens->array[cmd.tokens->length] = tokens->array[c->j];
		++(c->j);
		++(cmd.tokens->length);
	}
	ft_vector_add(c->commands, &cmd, sizeof(t_command));
	c->cmd_type = SIMPLE_CMD;
}

static void	init_vars(t_construct_commands *c)
{
	c->commands = ft_vector_new();
	c->cmd_type = SIMPLE_CMD;
	c->i = 0;
	c->j = 0;
}

t_vector	*construct_commands(t_vector *tokens)
{
	t_construct_commands c;

	init_vars(&c);
	while (c.i < tokens->length)
	{
		c.token = (t_token*)tokens->array[c.i]->content;
		if (c.token->type == SEMI)
		{
			if (c.i != c.j)
				add_command(tokens, &c);
			ft_vector_remove_at(tokens, c.i, del_token);
			continue ;
		}
		else if (c.token->type == PIPELINE)
			c.cmd_type = PIPE_SEQ;
		++(c.i);
	}
	if (c.i > c.j)
		add_command(tokens, &c);
	return (c.commands);
}
