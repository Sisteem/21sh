/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagtab <ylagtab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/08 09:47:37 by ylagtab           #+#    #+#             */
/*   Updated: 2021/02/28 11:06:50 by ylagtab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one.h"

t_vector	*g_shell_env;

void		handler(int unused)
{
	(void)unused;
}

char		*read_cmd(void)
{
	char *cmd;
	char *tmp;

	ft_printf(1, "$ ");
	if (get_next_line(0, &cmd) < 0)
		exit(1);
	if (cmd == NULL)
	{
		ft_printf(1, "exit\n");
		exit(0);
	}
	if (*cmd == '\0')
		return (cmd);
	tmp = cmd;
	cmd = ft_strtrim(cmd);
	free(tmp);
	return (cmd);
}

static void	free_mini_env(t_vector *mini_env)
{
	size_t		i;

	i = 0;
	while (i < mini_env->length)
	{
		free_env_var(mini_env->array[i]->content, 0);
		free(mini_env->array[i]);
		++i;
	}
	free(mini_env->array);
	mini_env = NULL;
}

static int	shell_main(char *arg_cmd)
{
	t_vector	*commands;
	char		*line;
	int			ret_status;

	while (1337)
	{
		g_errno = EXIT_SUCCESS;
		line = arg_cmd ? ft_strdup(arg_cmd) : read_cmd();
		commands = parse_command(line);
		ft_strdel(&line);
		if (commands != NULL)
		{
			expansion(commands);
			ret_status = exec_commands(commands);
		}
		if (arg_cmd != NULL)
			return (g_errno);
	}
	return (0);
}

int			main(int ac, char *av[], char *envp[])
{
	t_vector	mini_env;
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
	free_mini_env(&mini_env);
	return (exit_value);
}
