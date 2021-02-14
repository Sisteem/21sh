/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagtab <ylagtab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/08 09:47:37 by ylagtab           #+#    #+#             */
/*   Updated: 2021/02/14 10:12:49 by ylagtab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one.h"

t_vector	*g_shell_env;

const char *g_tokens_keys[] = {
	"NONE",
	"WORD",
	"IO_NUMBER",
	"SEMI",
	"PIPELINE",
	"DLESSDASH",
	"DLESS",
	"LESS",
	"ANDDGREAT",
	"ANDGREAT",
	"DGREAT",
	"GREATANDDASH",
	"GREATAND",
	"GREAT",
};

void	print_tokens(t_vector *tokens)
{
	t_token	*t;
	size_t	i;

	i = 0;
	while (i < tokens->length)
	{
		t = (t_token*)tokens->array[i]->content;
		ft_printf(1, "%s: ", g_tokens_keys[t->type]);
		if (t->type == WORD)
			ft_printf(1, "%s", (char*)t->data);
		if (t->type == IO_NUMBER)
			ft_printf(1, "%d", *((int*)t->data));
		ft_printf(1, "\n");
		i++;
	}
}

char		*read_cmd(void)
{
	char *cmd;
	char *tmp;

	ft_printf(1, "$ ");
	if (get_next_line(0, &cmd) < 0)
		exit(1);
	if (*cmd == '\0')
		return (cmd);
	tmp = cmd;
	cmd = ft_strtrim(cmd);
	free(tmp);
	return (cmd);
}

int		main(int ac, char *av[], char *envp[])
{
	t_vector	*args;
	char		*cmd;

	g_shell_env = env_init(envp);
	if (ac == 1)
		cmd = read_cmd();
	else
		cmd = av[ac - 1];
	ft_printf(1, "cmd: %s\n", cmd);
	args = parse_command(cmd);
	(void)args;
	return (0);
}
