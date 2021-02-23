/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagtab <ylagtab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 10:11:12 by ylagtab           #+#    #+#             */
/*   Updated: 2021/02/23 08:26:29 by ylagtab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "internal.h"

int	exec_commands(t_vector *commands)
{
	t_command	*cmd;
	pid_t		child_pid;
	size_t		i;
	int			return_value;

	i = 0;
	while (i < commands->length)
	{
		child_pid = fork();
		cmd = (t_command*)commands->array[i]->content;
		if (child_pid == 0)
		{
			if (cmd->type == SIMPLE_CMD)
				return (exec_simple_command(cmd->tokens));
			return (exec_pipe_sequence(cmd->tokens));
		}
		waitpid(child_pid, &return_value, 0);
		++i;

	}
	return (return_value);
}
