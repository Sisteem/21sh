/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   twenty_one.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-idri <mel-idri@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/08 09:51:09 by ylagtab           #+#    #+#             */
/*   Updated: 2021/03/14 11:03:03 by mel-idri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TWENTY_ONE_H
# define TWENTY_ONE_H

# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <signal.h>
# include <fcntl.h>

# include "../libft/libft.h"
# include "../readline/readline.h"
# include "typedefs.h"
# include "errors/errors.h"
# include "parser/parser.h"
# include "expansion/expansion.h"
# include "redirections/redirections.h"
# include "execution/execution.h"
# include "built_in/built_in.h"

# define PATH_MAX 1024
# define PS1 "$ "
# define PS2 "> "

extern t_vector	*g_shell_env;

int		read_command_line(char **cmd);
void	del_command(void *content, size_t content_size);
void	del_token(void *content, size_t content_size);
void	del_command_without_tokens(void *content, size_t content_size);
pid_t	fork_process(void);

#endif
