/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_simple_command.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagtab <ylagtab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/14 17:12:34 by ylagtab           #+#    #+#             */
/*   Updated: 2021/02/28 09:28:18 by ylagtab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "internal.h"

static char		**tokens_to_strings_array(t_vector *tokens)
{
	t_token	*tk;
	char	**array;
	size_t	i;

	i = 0;
	array = (char**)ft_malloc((tokens->length + 1) * sizeof(char*));
	array[tokens->length] = NULL;
	while (i < tokens->length)
	{
		tk = (t_token*)tokens->array[i]->content;
		array[i] = (char*)tk->data;
		++i;
	}
	return (array);
}

int				exec_simple_command(t_vector *tokens, t_bool run_in_child)
{
	char	*exe_path;
	char	**args;
	char	**envp;
	int		exit_status;

	remove_quotes(tokens);
	if (perform_redirections(tokens) == -1)
		return (g_errno);
	if (tokens->length == 0)
		return (EXIT_SUCCESS);
	args = tokens_to_strings_array(tokens);
	if (is_built_in(args[0]))
		return (run_built_in(args, ft_strings_array_length(args + 1)));
	exe_path = get_executable_pathname(tokens->array[0]->content);
	if (exe_path == NULL)
		return (g_errno);
	envp = shell_env_to_envp(g_shell_env);
	if (run_in_child == FALSE || fork() == 0)
	{
		execve(exe_path, args, envp);
		return (EUNK);
	}
	else
		wait(&exit_status);
	return (exit_status);
}
