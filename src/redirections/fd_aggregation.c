/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_aggregation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagtab <ylagtab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 08:19:42 by ylagtab           #+#    #+#             */
/*   Updated: 2021/03/10 16:36:08 by ylagtab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "internal.h"

static int	str_is_number(char *str)
{
	while (*str)
	{
		if (*str < '0' || *str > '9')
			return (0);
		++str;
	}
	return (1);
}

int			fd_aggregation(int io_number, t_token_type type, char *word)
{
	if (io_number == -1)
	{
		if (type == GREATAND)
			io_number = STDOUT_FILENO;
		if (type == LESSAND)
			io_number = STDIN_FILENO;
	}
	if (str_is_number(word))
	{
		if (dup2(ft_atoi(word), io_number) == -1)
		{
			g_errno = EREDIRECTION;
			return (-1);
		}
	}
	else if (ft_strequ(word, "-"))
		close_fd(io_number, 0);
	return (EXIT_SUCCESS);
}
