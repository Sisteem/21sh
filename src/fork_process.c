/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-idri <mel-idri@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/14 11:00:29 by mel-idri          #+#    #+#             */
/*   Updated: 2021/03/14 11:02:54 by mel-idri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one.h"

pid_t	fork_process(void)
{
	pid_t pid;

	pid = fork();
	if (pid < 0)
	{
		ft_printf(2, "fork error");
		exit(EXIT_FAILURE);
	}
	return (pid);
}
