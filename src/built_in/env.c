/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagtab <ylagtab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/02 08:58:23 by vanderwolk        #+#    #+#             */
/*   Updated: 2021/02/28 11:12:37 by ylagtab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one.h"

static int	is_valid_name(char *name)
{
	size_t	i;

	if (!ft_isalpha(name[0]) && name[0] != '_')
		return (0);
	i = 1;
	while (name[i])
	{
		if (!ft_isalnum(name[i]) && name[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

int			env_set(char **args, size_t args_len)
{
	char	*usage;

	usage = "usage: setenv name value\nname: [a-zA-Z_][a-zA-Z0-9_]*\n";
	if (args_len != 2)
	{
		ft_printf(2, "minishell: setenv: wrong number of arguments\n%s", usage);
		return (1);
	}
	if (!is_valid_name(args[1]))
	{
		ft_printf(2, "minishell: setenv: not valid name\n%s", usage);
		return (1);
	}
	env_remove(args[1]);
	env_add(args[0], args[1]);
	return (0);
}

int			env_unset(char **args, size_t args_len)
{
	(void)args_len;
	while (*args)
	{
		if (!is_valid_name(*args))
		{
			ft_printf(2, "minishell: unsetenv: %s not valid name\n", *args);
		}
		env_remove(*args);
		++args;
	}
	return (0);
}

int			env(char **args, size_t args_len)
{
	t_env_var	var;
	size_t		i;
	char		*usage;

	usage = "usage: env\n";
	(void)args;
	if (args_len != 1)
	{
		ft_printf(2, "minishell: env: wrong number of arguments\n%s", usage);
		return (1);
	}
	i = 0;
	while (i < g_shell_env->length)
	{
		var = *(t_env_var *)(g_shell_env->array[i]->content);
		ft_printf(1, "%s=%s\n", var.key, var.value);
		i++;
	}
	return (0);
}
