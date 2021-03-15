/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-idri <mel-idri@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/02 08:58:23 by vanderwolk        #+#    #+#             */
/*   Updated: 2021/03/15 08:35:25 by mel-idri         ###   ########.fr       */
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
		ft_printf(2, "21sh: setenv: wrong number of arguments\n%s", usage);
		return (1);
	}
	if (!is_valid_name(args[0]))
	{
		ft_printf(2, "21sh: setenv: not valid name\n%s", usage);
		return (1);
	}
	env_remove(args[0]);
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
			ft_printf(2, "21sh: unsetenv: %s not valid name\n", *args);
		}
		env_remove(*args);
		++args;
	}
	return (0);
}

void		print_all_env_vars(void)
{
	t_env_var	var;
	size_t		i;

	i = 0;
	while (i < g_shell_env->length)
	{
		var = *(t_env_var *)(g_shell_env->array[i]->content);
		ft_printf(1, "%s=%s\n", var.key, var.value);
		i++;
	}
}

int			env(char **args)
{
	t_vector	*tmp_shell_env;
	char		*equal_sign;
	size_t		i;

	i = 0;
	tmp_shell_env = env_dup(g_shell_env);
	while ((equal_sign = ft_strchr(args[i], '=')))
	{
		if (args[i][0] == '=')
		{
			ft_printf(2, "21sh: env: value is required\n");
			ft_vector_free(tmp_shell_env, TRUE, free_env_var);
			return (EXIT_FAILURE);
		}
		*equal_sign = '\0';
		set_env_var(args[i], equal_sign + 1);
		i++;
	}
	if (args[i])
		run_executable(args + i, TRUE);
	else
		print_all_env_vars();
	ft_vector_free(g_shell_env, TRUE, free_env_var);
	g_shell_env = tmp_shell_env;
	return (EXIT_SUCCESS);
}
