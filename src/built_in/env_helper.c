/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_helper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-idri <mel-idri@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 08:08:30 by mel-idri          #+#    #+#             */
/*   Updated: 2021/03/15 15:34:45 by mel-idri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "internal.h"

void		set_env_var(char *name, char *value)
{
	env_remove(name);
	env_add(name, value);
}

void		reset_env(t_vector *tmp_shell_env)
{
	ft_vector_free(g_shell_env, TRUE, free_env_var);
	g_shell_env = tmp_shell_env;
}

t_vector	*env_dup(t_vector *env)
{
	t_vector	*tmp_env;
	char		**envp;

	envp = shell_env_to_envp(env);
	tmp_env = env_init(envp);
	ft_free_strings_array(envp);
	return (tmp_env);
}

static void	print_all_env_vars(void)
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

void		run_env(char **args, size_t utility_index)
{
	if (args[utility_index])
		run_executable(args + utility_index, TRUE);
	else
		print_all_env_vars();
}
