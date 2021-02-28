/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_built_in.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagtab <ylagtab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 16:02:18 by ylagtab           #+#    #+#             */
/*   Updated: 2021/02/28 11:13:05 by ylagtab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "internal.h"

int		is_built_in(char *str)
{
	if (ft_strequ(str, "env"))
		return (1);
	else if (ft_strequ(str, "setenv"))
		return (1);
	else if (ft_strequ(str, "unsetenv"))
		return (1);
	else if (ft_strequ(str, "echo"))
		return (1);
	else if (ft_strequ(str, "cd"))
		return (1);
	else if (ft_strequ(str, "exit"))
		return (1);
	return (0);
}
