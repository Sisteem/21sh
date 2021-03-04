/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   twenty_one.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagtab <ylagtab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/08 09:51:09 by ylagtab           #+#    #+#             */
/*   Updated: 2021/03/04 12:03:23 by ylagtab          ###   ########.fr       */
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
# include "typedefs.h"
# include "errors/errors.h"
# include "parser/parser.h"
# include "expansion/expansion.h"
# include "redirections/redirections.h"
# include "execution/execution.h"
# include "built_in/built_in.h"

# define PATH_MAX 1024

extern t_vector	*g_shell_env;

void	del_command(void *content, size_t content_size);
void	del_token(void *content, size_t content_size);
void	del_command_without_tokens(void *content, size_t content_size);

#endif
