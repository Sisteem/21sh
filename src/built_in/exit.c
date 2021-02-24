/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagtab <ylagtab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/02 12:07:00 by vanderwolk        #+#    #+#             */
/*   Updated: 2021/02/24 16:37:43 by ylagtab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one.h"

static int	str_is_number(char *s)
{
	size_t i;

	i = 0;
	while (s[i])
	{
		if (!ft_isdigit(s[i]))
			return (0);
		i++;
	}
	return (1);
}

int		exit_shell(char **args, size_t args_len)
{
	char *usage;

	usage = "usage: exit [number]\n";
	if (args_len > 0 && !str_is_number(args[0]))
	{
		ft_printf(2, "minishell: exit: `%s` numeric argument required\n%s",
			args[0], usage);
		exit(255);
	}
	if (args_len > 1)
	{
		ft_printf(2, "minishell: exit: too many arguments\n%s", usage);
		return (1);
	}
	exit(args_len == 0 ? 0 : ft_atoi(args[0]));
	return (0);
}
