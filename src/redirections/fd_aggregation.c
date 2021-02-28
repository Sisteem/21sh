/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_aggregation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagtab <ylagtab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 08:19:42 by ylagtab           #+#    #+#             */
/*   Updated: 2021/02/28 09:33:57 by ylagtab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "internal.h"

int	fd_aggregation(int old_fd, int new_fd)
{
	if (new_fd == -1)
		new_fd = STDOUT_FILENO;
	if (dup2(old_fd, new_fd) == -1)
	{
		g_errno = EREDIRECTION;
		return (-1);
	}
	return (EXIT_SUCCESS);
}
