/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_built_in.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagtab <ylagtab@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/02 09:30:38 by vanderwolk        #+#    #+#             */
/*   Updated: 2021/02/09 17:29:23 by ylagtab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one.h"

int			run_built_in(t_vector *mini_env, char **args, size_t args_len)
{
	if (ft_strcmp(args[0], "env") == 0)
		env(mini_env, args, args_len);
	else if (ft_strcmp(args[0], "setenv") == 0)
		env_set(mini_env, args, args_len);
	else if (ft_strcmp(args[0], "unsetenv") == 0)
		env_unset(mini_env, args, args_len);
	else if (ft_strcmp(args[0], "echo") == 0)
		echo(args + 1);
	else if (ft_strcmp(args[0], "cd") == 0)
		cd(mini_env, args, args_len);
	else if (ft_strcmp(args[0], "exit") == 0)
		exit_shell(args, args_len);
	else
		return (0);
	return (1);
}
