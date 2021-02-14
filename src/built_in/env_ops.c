/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_ops.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagtab <ylagtab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/18 16:52:12 by ylagtab           #+#    #+#             */
/*   Updated: 2021/02/13 18:20:35 by ylagtab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one.h"

void		free_env_var(void *content, size_t content_size)
{
	t_env_var *var;

	(void)content_size;
	var = (t_env_var *)(content);
	free(var->key);
	free(var->value);
	free(var);
}

static char	*escape_quotes_backslashes(char *str)
{
	char	*s;
	char	*first_part;
	char	*tmp;
	size_t	i;

	s = ft_strdup(str);
	i = 0;
	while (s[i])
	{
		if (s[i] == SINGLE_QUOTE || s[i] == DOUBLE_QUOTE || s[i] == BACK_SLASH)
		{
			first_part = ft_strsub(s, 0, i);
			tmp = s;
			s = ft_strglue(first_part, BACK_SLASH, s + i);
			ft_memdel((void **)&tmp);
			i++;
		}
		i++;
	}
	return (s);
}

char		*env_get(t_vector *mini_env, char *key)
{
	t_env_var	var;
	size_t		i;

	i = 0;
	while (i < mini_env->length)
	{
		var = *(t_env_var *)(mini_env->array[i]->content);
		if (ft_strcmp(key, var.key) == 0)
			return (escape_quotes_backslashes(var.value));
		i++;
	}
	return (NULL);
}

void		env_add(t_vector *mini_env, char *key, char *value)
{
	t_env_var var;

	var.key = ft_strdup(key);
	var.value = ft_strdup(value);
	ft_vector_add(mini_env, &var, sizeof(t_env_var));
}

void		env_remove(t_vector *mini_env, char *key)
{
	t_env_var	var;
	size_t		i;

	i = 0;
	while (i < mini_env->length)
	{
		var = *(t_env_var *)(mini_env->array[i]->content);
		if (ft_strcmp(key, var.key) == 0)
		{
			ft_vector_remove_at(mini_env, i, free_env_var);
			return ;
		}
		i++;
	}
}
