/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe_sequence.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagtab <ylagtab@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 09:27:29 by ylagtab           #+#    #+#             */
/*   Updated: 2021/03/03 15:53:53 by ylagtab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "internal.h"

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
			ft_perror(NULL, NULL, FALSE);
		}
		++i;
	}
	return (pipes);
}

static void	free_pipes_array(int **pipes, size_t count)
{
	size_t	i;

	i = 0;
	while (i < count)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		ft_memdel((void**)&(pipes[i]));
		++i;
	}
	free(pipes);
}

static int	exec_pipe_command(t_command *cmd, t_command_fds *cmd_fds)
{
	if (cmd_fds->in != -1)
		if (dup2(cmd_fds->in, STDIN_FILENO) == -1)
		{
			g_errno = EREDIRECTION;
			ft_perror(NULL, NULL, TRUE);
		}
	if (cmd_fds->out != -1)
		if (dup2(cmd_fds->out, STDOUT_FILENO) == -1)
		{
			g_errno = EREDIRECTION;
			ft_perror(NULL, NULL, TRUE);
		}
	return (exec_simple_command(cmd->tokens, FALSE));
}

int			exec_pipe_sequence(t_vector *tokens)
{
	t_command_fds	cmd_fds;
	t_vector		commands;
	int				**pipes;
	int				exit_status;
	size_t			i;

	split_pipe_sequence_commands(tokens, &commands);
	pipes = create_pipes(commands.length - 1);
	i = 0;
	while (i < commands.length)
	{
		cmd_fds.in = i == 0 ? -1 : pipes[i - 1][0];
		cmd_fds.out = i == commands.length - 1 ? -1 : pipes[i][1];
		if (fork() == 0)
			return (exec_pipe_command(commands.array[i]->content, &cmd_fds));
		close(cmd_fds.out);
		++i;
	}
	while (wait(&exit_status) != -1)
		;
	free_pipes_array(pipes, commands.length - 1);
	ft_vector_free(&commands, FALSE, del_command);
	return (exit_status);
}
