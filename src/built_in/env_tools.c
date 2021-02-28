/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagtab <ylagtab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/30 03:05:41 by vanderwolk        #+#    #+#             */
/*   Updated: 2021/02/24 16:22:32 by ylagtab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one.h"

static size_t	env_len(char **env)
{
	size_t len;

	len = 0;
	while (env[len])
		len++;
	return (len);
}

t_vector		*env_init(char **envp)
{
	t_vector	*sh_env;
	t_env_var	var;
	size_t		equal_index;
	size_t		i;
	size_t		len;

	len = env_len(envp);
	sh_env = ft_vector_new_capacity(len);
	i = 0;
	while (i < len)
	{
		equal_index = ft_strichr(envp[i], '=');
		var.key = ft_strsub(envp[i], 0, equal_index);
		if (ft_strcmp(var.key, "SHELL") == 0)
			var.value = ft_strdup("21sh");
		else
			var.value = ft_strdup(envp[i] + equal_index + 1);
		ft_vector_add(sh_env, &var, sizeof(t_env_var));
		i++;
	}
	return (sh_env);
}

char			**shell_env_to_envp(t_vector *shell_env)
{
	t_env_var	var;
	char		**envp;
	size_t		i;

	i = 0;
	envp = (char **)ft_malloc((shell_env->length + 1) * sizeof(char *));
	while (i < shell_env->length)
	{
		var = *(t_env_var *)(shell_env->array[i]->content);
		envp[i] = ft_strglue(var.key, '=', var.value);
		i++;
	}
	envp[i] = NULL;
	return (envp);
}
