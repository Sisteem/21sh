/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe_sequence.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagtab <ylagtab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 09:27:29 by ylagtab           #+#    #+#             */
/*   Updated: 2021/02/24 15:58:57 by ylagtab          ###   ########.fr       */
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

static int	**create_pipes(size_t count)
{
	int		**pipes;
	size_t	i;

	i = 0;
	pipes = (int**)ft_malloc(count * sizeof(int*));
	while (i < count)
	{
		pipes[i] = (int*)ft_malloc(2 * sizeof(int));
		if (pipe(pipes[i]) == -1)
		{
			g_errno = EUNK;
			ft_perror(NULL, NULL, TRUE);
		}
		++i;
	}
	return (pipes);
}

int	**close_pipes(int **pipes, size_t count)
{
	size_t	i;

	i = 0;
	while (i < count)
	{
		if (close(pipes[i][0]) == -1 || close(pipes[i][1]) == -1)
		{
			g_errno = EUNK;
			ft_perror(NULL, NULL, TRUE);
		}
		ft_memdel((void**)&(pipes[i]));
		++i;
	}
	free(pipes);
	return (pipes);
}

static int	exec_pipe_command(t_command *cmd, t_command_fds *command_fds)
{
	if (command_fds->in != -1)
	{
		if (dup2(command_fds->in, STDIN_FILENO) == -1)
		{
			g_errno = EREDIRECTION;
			ft_perror(NULL, NULL, TRUE);
		}
		close(command_fds->in);
	}

	if (command_fds->out != -1)
	{
		if (dup2(command_fds->out, STDOUT_FILENO) == -1)
		{
			g_errno = EREDIRECTION;
			ft_perror(NULL, NULL, TRUE);
		}
		close(command_fds->out);
	}
	if (command_fds->to_close[0] != -1)
		close(command_fds->to_close[0]);
	if (command_fds->to_close[1] != -1)
		close(command_fds->to_close[1]);
	return (exec_simple_command(cmd->tokens));
}

int	exec_pipe_sequence(t_vector *tokens)
{
	t_command_fds	command_fds;
	t_vector		commands;
	int				**pipes;
	t_command		*cmd;
	size_t			i;

	split_pipe_sequence_commands(tokens, &commands);
	pipes = create_pipes(commands.length - 1);
	i = 0;
	while (i < commands.length)
	{
		cmd = commands.array[i]->content;
		command_fds.in = i == 0 ? -1 : pipes[i - 1][0];
		command_fds.out = i == commands.length - 1 ? -1 : pipes[i][1];
		command_fds.to_close[0] = i == commands.length - 1 ? -1 : pipes[i][0];
		command_fds.to_close[1] = i == 0 ? -1 : pipes[i - 1][1];
		if (fork() == 0)
			return (exec_pipe_command(cmd, &command_fds));
		++i;
	}
	close_pipes(pipes, commands.length - 1);
	while (wait(NULL) != -1)
		;
	return (0);
}
