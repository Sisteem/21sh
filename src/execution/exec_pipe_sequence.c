/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe_sequence.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-idri <mel-idri@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 09:27:29 by ylagtab           #+#    #+#             */
/*   Updated: 2021/03/14 11:03:45 by mel-idri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "internal.h"

static int	**create_fds(size_t count)
{
	int		**fds;
	size_t	i;

	i = 0;
	fds = (int**)ft_malloc(count * sizeof(int*));
	while (i < count)
	{
		fds[i] = (int*)ft_malloc(2 * sizeof(int));
		if (pipe(fds[i]) == -1)
		{
			g_errno = EUNK;
			ft_perror(NULL, NULL, FALSE);
		}
		++i;
	}
	return (fds);
}

static void	close_fds(int **fds, size_t count)
{
	size_t	i;

	i = 0;
	while (i < count)
	{
		close(fds[i][0]);
		close(fds[i][1]);
		++i;
	}
}

static void	free_fds_array(int **fds, size_t count)
{
	size_t	i;

	i = 0;
	while (i < count)
	{
		close(fds[i][0]);
		close(fds[i][1]);
		ft_memdel((void**)&(fds[i]));
		++i;
	}
	free(fds);
}

static int	exec_pipe_command(
	t_command *cmd, size_t index, int **fds, size_t fds_count)
{
	int exit_status;

	if (index > 0)
		if (dup2(fds[index - 1][0], STDIN_FILENO) == -1)
		{
			g_errno = EREDIRECTION;
			ft_perror(NULL, NULL, TRUE);
		}
	if (index < fds_count)
		if (dup2(fds[index][1], STDOUT_FILENO) == -1)
		{
			g_errno = EREDIRECTION;
			ft_perror(NULL, NULL, TRUE);
		}
	close_fds(fds, fds_count);
	exit_status = exec_simple_command(cmd, FALSE);
	exit(exit_status);
}

int			exec_pipe_sequence(t_command *cmd)
{
	t_vector		commands;
	int				**fds;
	int				exit_status;
	size_t			fds_count;
	size_t			i;

	split_pipe_sequence_commands(cmd->tokens, &commands);
	if (prepare_commands_here_docs(&commands) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	fds_count = commands.length - 1;
	fds = create_fds(fds_count);
	i = 0;
	while (i < commands.length)
	{
		if (fork_process() == 0)
			exec_pipe_command(commands.array[i]->content, i, fds, fds_count);
		++i;
	}
	close_fds(fds, fds_count);
	while (wait(&exit_status) != -1)
		;
	free_fds_array(fds, fds_count);
	ft_vector_free(&commands, FALSE, del_command_without_tokens);
	return (exit_status);
}
