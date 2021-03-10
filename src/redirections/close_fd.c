/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_fd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagtab <ylagtab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/27 15:05:47 by ylagtab           #+#    #+#             */
/*   Updated: 2021/03/10 16:16:51 by ylagtab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "internal.h"

void	close_fd(int io_number, int redi_type)
{
	if (io_number == -1)
	{
		if (redi_type == REDI_OUT)
			io_number = STDOUT_FILENO;
		if (redi_type == REDI_IN)
			io_number = STDIN_FILENO;
	}
	close(io_number);
}
