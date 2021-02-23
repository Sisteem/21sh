/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   internal.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagtab <ylagtab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/14 17:11:27 by ylagtab           #+#    #+#             */
/*   Updated: 2021/02/23 16:57:29 by ylagtab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERNAL_H
# define INTERNAL_H

# include "twenty_one.h"

typedef struct	s_command_fds
{
	int	input_fd_to_dup;
	int	output_fd_to_dup;
	int	input_fd_to_close;
	int	output_fd_to_close;
}				t_command_fds;


int		exec_simple_command(t_vector *tokens);
int		exec_pipe_sequence(t_vector *tokens);
int		exec_cmd(t_command *cmd);

#endif
