/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagtab <ylagtab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/08 09:47:37 by ylagtab           #+#    #+#             */
/*   Updated: 2021/03/08 11:07:48 by ylagtab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one.h"

t_vector	*g_shell_env;

void		handler(int unused)
{
	(void)unused;
}

static void	free_shell_env(t_vector *shell_env)
{
	size_t		i;

	i = 0;
	while (i < shell_env->length)
	{
		free_env_var(shell_env->array[i]->content, 0);
		free(shell_env->array[i]);
		++i;
	}
	free(shell_env->array);
	shell_env = NULL;
}

static int	get_command(char **cmd)
{
	int ret;

	if (*cmd != NULL)
		return (LINE);
	ret = read_command_line(cmd);
	if (ret == EXIT)
	{
		ft_printf(1, "exit\n");
		exit(0);
	}
	if (ret == ERROR)
		exit(1);
	return (ret);
}

static int	shell_main(char *arg_cmd)
{
	t_vector	*commands;
	char		*cmd;
	int			ret_status;

	while (1337)
	{
		g_errno = EXIT_SUCCESS;
		cmd = ft_strdup(arg_cmd);
		if (get_command(&cmd) == INTERRUPTED)
			continue ;
		commands = parse_command(cmd);
		ft_strdel(&cmd);
		if (commands != NULL)
		{
			expansion(commands);
			ret_status = exec_commands(commands);
		}
		ft_vector_free(commands, TRUE, del_command);
		commands = NULL;
		if (arg_cmd != NULL)
			return (g_errno);
	}
	return (0);
}

int			main(int ac, char *av[], char *envp[])
{
	t_vector	shell_env;
	int			exit_value;

	exit_value = 1;
	signal(SIGINT, &handler);
	g_shell_env = env_init(envp);
	if (ac == 3 && ft_strcmp(av[1], "-c") == 0)
		exit_value = shell_main(av[2]);
	if (ac == 1)
		exit_value = shell_main(NULL);
	if (exit_value != 0)
		ft_printf(2, "Error\nusage: ./21sh [-c command]\n");
	free_shell_env(&shell_env);
	return (exit_value);
}
