/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_and_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-idri <mel-idri@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 16:06:17 by mel-idri          #+#    #+#             */
/*   Updated: 2021/03/15 16:11:10 by mel-idri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "internal.h"

void	fork_and_exec(t_vector *commands, int **fds, size_t fds_count)
{
	size_t i;

	i = 0;
	while (i < commands->length)
	{
		if (fork_process() == 0)
			exec_pipe_command(commands->array[i]->content, i, fds, fds_count);
		++i;
	}
}
