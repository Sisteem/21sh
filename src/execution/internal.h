/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   internal.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-idri <mel-idri@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/14 17:11:27 by ylagtab           #+#    #+#             */
/*   Updated: 2021/03/15 16:15:49 by mel-idri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERNAL_H
# define INTERNAL_H

# include "twenty_one.h"

typedef struct	s_command_fds
{
	int	in;
	int	out;
}				t_command_fds;

int				exec_simple_command(t_command *cmd, t_bool run_in_child);
int				exec_pipe_sequence(t_command *cmd);
char			*get_executable_pathname(char *str);
void			split_pipe_sequence_commands(t_vector *tokens,
					t_vector *commands);
void			fork_and_exec(t_vector *commands, int **fds, size_t fds_count);
int				exec_pipe_command(
					t_command *cmd, size_t index, int **fds, size_t fds_count);

#endif
