/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_pipe_sequence_commands.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagtab <ylagtab@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/28 11:24:54 by ylagtab           #+#    #+#             */
/*   Updated: 2021/03/12 18:28:20 by ylagtab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "internal.h"

static void	add_command(
	t_vector *tokens, t_vector *commands, size_t *i, size_t *j)
{
	t_command	cmd;

	cmd.type = SIMPLE_CMD;
	cmd.here_docs = ft_vector_new();
	cmd.tokens = ft_vector_new_capacity(*i - *j);
	while (*j < *i)
	{
		cmd.tokens->array[cmd.tokens->length] = tokens->array[*j];
		++(*j);
		++(cmd.tokens->length);
	}
	ft_vector_add(commands, &cmd, sizeof(t_command));
}

void		split_pipe_sequence_commands(t_vector *tokens, t_vector *commands)
{
	t_token	*token;
	size_t	i;
	size_t	j;

	ft_vector_init(commands);
	i = 0;
	j = 0;
	while (i < tokens->length)
	{
		token = (t_token*)tokens->array[i]->content;
		if (token->type == PIPELINE)
		{
			add_command(tokens, commands, &i, &j);
			++j;
		}
		++i;
	}
	add_command(tokens, commands, &i, &j);
}
