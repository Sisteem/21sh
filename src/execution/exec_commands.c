/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagtab <ylagtab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 10:11:12 by ylagtab           #+#    #+#             */
/*   Updated: 2021/02/27 17:40:21 by ylagtab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "internal.h"

int			g_stdin_fd;
int			g_stdout_fd;
int			g_stderr_fd;

static int	save_standard_fds(void)
{
	if ((g_stdin_fd = dup(STDIN_FILENO)) == -1)
	{
		ft_strerror(EUNK, NULL, NULL, FALSE);
		return (-1);
	}
	if ((g_stdout_fd = dup(STDOUT_FILENO)) == -1)
	{
		ft_strerror(EUNK, NULL, NULL, FALSE);
		return (-1);
	}
	if ((g_stderr_fd = dup(STDERR_FILENO)) == -1)
	{
		ft_strerror(EUNK, NULL, NULL, FALSE);
		return (-1);
	}
	return (EXIT_SUCCESS);
}

static int	restore_standard_fds(void)
{
	if (dup2(g_stdin_fd, STDIN_FILENO) == -1 || close(g_stdin_fd) == -1)
	{
		ft_strerror(EUNK, NULL, NULL, FALSE);
		return (-1);
	}
	if (dup2(g_stdout_fd, STDOUT_FILENO) == -1 || close(g_stdout_fd) == -1)
	{
		ft_strerror(EUNK, NULL, NULL, FALSE);
		return (-1);
	}
	if (dup2(g_stderr_fd, STDERR_FILENO) == -1 || close(g_stderr_fd) == -1)
	{
		ft_strerror(EUNK, NULL, NULL, FALSE);
		return (-1);
	}
	return (EXIT_SUCCESS);
}

int			exec_commands(t_vector *commands)
{
	t_command	*cmd;
	size_t		i;
	int			ret_value;

	i = 0;
	while (i < commands->length)
	{
		if (save_standard_fds() == -1)
			return (EUNK);
		cmd = (t_command*)commands->array[i]->content;
		if (cmd->type == SIMPLE_CMD)
			ret_value = exec_simple_command(cmd->tokens, TRUE);
		else
			ret_value = exec_pipe_sequence(cmd->tokens);
		++i;
		if (restore_standard_fds() == -1)
			return (EUNK);
	}
	return (ret_value);
}
