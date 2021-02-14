/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   twenty_one.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagtab <ylagtab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/08 09:51:09 by ylagtab           #+#    #+#             */
/*   Updated: 2021/02/13 14:47:08 by ylagtab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TWENTY_ONE_H
# define TWENTY_ONE_H

# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <signal.h>

# include "../libft/libft.h"
# include "parser/parser.h"
# include "./expansion/expansion.h"
# include "./built_in/built_in.h"

# define PATH_MAX 1024

typedef enum	e_error
{
	EACCESS = 1,
	ENOTFOUND,
	ENOTDIR,
	ENAMETOOLONG,
	ENOHOME,
	ENOOLPPWD,
	EPATHISDIR,
	EUNK
}				t_error;

extern t_vector	*g_shell_env;

void	print_tokens(t_vector *tokens);

#endif
