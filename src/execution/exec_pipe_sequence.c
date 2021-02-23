/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe_sequence.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagtab <ylagtab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 09:27:29 by ylagtab           #+#    #+#             */
/*   Updated: 2021/02/22 18:26:24 by ylagtab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "internal.h"

static void	add_command(
	t_vector *tokens, t_vector *commands, size_t *i, size_t *j)
{
	t_command	cmd;

	cmd.type = SIMPLE_CMD;
	cmd.tokens = ft_vector_new_capacity(*i - *j);
	while (*j < *i)
	{
		cmd.tokens->array[cmd.tokens->length] = tokens->array[*j];
		++(*j);
		++(cmd.tokens->length);
	}
	ft_vector_add(commands, &cmd, sizeof(t_command));
}

static void	split_pipe_sequence_commands(t_vector *tokens, t_vector *commands)
{
	t_token	*token;
	size_t	i;
	size_t	j;

	ft_vector_init(commands);
	i = 0;
	j = 0;
	while (i < tokens->length)
	{
		token = (t_token*)tokens->array[i]->content;
		if (token->type == PIPELINE)
		{
			add_command(tokens, commands, &i, &j);
			++j;
		}
		++i;
	}
	add_command(tokens, commands, &i, &j);
}

static int	**create_pipes_fd(size_t count)
{
	int		**pipes_fds;
	size_t	i;

	i = 0;
	pipes_fds = (int**)ft_malloc(count * sizeof(int*));
	while (i < count)
	{
		pipes_fds[i] = (int*)ft_malloc(2 * sizeof(int));
		if (pipe(pipes_fds[i]) == -1)
		{
			g_errno = EUNK;
			ft_perror(NULL, NULL, TRUE);
		}
		++i;
	}
	return (pipes_fds);
}

static int	exec_pipe_command(t_command *cmd, t_command_fds *command_fds)
{
	if (command_fds->in != -1)
		if (dup2(command_fds->in, STDIN_FILENO) == -1)
		{
			g_errno = EREDIRECTION;
			ft_perror(NULL, NULL, TRUE);
		}
	if (command_fds->out != -1)
		if (dup2(command_fds->out, STDOUT_FILENO) == -1)
		{
			g_errno = EREDIRECTION;
			ft_perror(NULL, NULL, TRUE);
		}
	return (exec_simple_command(cmd->tokens));
}

int	exec_pipe_sequence(t_vector *tokens)
{
	t_command_fds	command_fds;
	t_vector		commands;
	int				**pipes_fds;
	t_command		*cmd;
	size_t			i;

	split_pipe_sequence_commands(tokens, &commands);
	pipes_fds = create_pipes_fd(commands.length - 1);
	i = 0;
	while (i < commands.length)
	{
		cmd = commands.array[i]->content;
		command_fds.in = i == 0 ? -1 : pipes_fds[i - 1][0];
		command_fds.out = i == commands.length - 1 ? -1 : pipes_fds[i][1];
		if (fork() == 0)
			return (exec_pipe_command(cmd, &command_fds));
		++i;
	}
	while (waitpid(-1, NULL, 0) != -1)
		;
	return (0);
}
