/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_built_in.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-idri <mel-idri@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/02 09:30:38 by vanderwolk        #+#    #+#             */
/*   Updated: 2021/03/14 18:33:49 by mel-idri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one.h"

int		run_built_in(char **args, size_t args_len)
{
	if (ft_strcmp(args[0], "env") == 0)
		return (env(args + 1));
	else if (ft_strcmp(args[0], "setenv") == 0)
		return (env_set(args + 1, args_len));
	else if (ft_strcmp(args[0], "unsetenv") == 0)
		return (env_unset(args + 1, args_len));
	else if (ft_strcmp(args[0], "echo") == 0)
		return (echo(args + 1));
	else if (ft_strcmp(args[0], "cd") == 0)
		return (cd(args + 1, args_len));
	else if (ft_strcmp(args[0], "exit") == 0)
		return (exit_shell(args + 1, args_len));
	return (1);
}
