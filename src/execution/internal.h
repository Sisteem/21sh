/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   internal.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagtab <ylagtab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/14 17:11:27 by ylagtab           #+#    #+#             */
/*   Updated: 2021/02/28 09:29:02 by ylagtab          ###   ########.fr       */
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

int		exec_simple_command(t_vector *tokens, t_bool run_in_child);
int		exec_pipe_sequence(t_vector *tokens);
char	*get_executable_pathname(t_token *cmd);

#endif
