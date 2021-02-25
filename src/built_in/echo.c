/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagtab <ylagtab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/02 11:44:12 by vanderwolk        #+#    #+#             */
/*   Updated: 2021/02/25 11:45:41 by ylagtab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one.h"

int	echo(char **args)
{
	size_t	i;

	i = 0;
	while (args[i])
	{
		ft_printf(1, args[i]);
		if (args[i + 1])
			ft_printf(1, " ");
		i++;
	}
	ft_printf(1, "\n");
	return (EXIT_SUCCESS);
}
