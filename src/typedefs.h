/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   typedefs.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagtab <ylagtab@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 12:11:22 by ylagtab           #+#    #+#             */
/*   Updated: 2021/03/12 17:37:55 by ylagtab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPEDEFS_H
# define TYPEDEFS_H

typedef enum	e_token_type
{
	NONE,
	NEWLINE,
	WORD,
	SEMI,
	PIPELINE,
	IO_NUMBER,
	GREAT,
	DGREAT,
	ANDGREAT,
	ANDDGREAT,
	LESS,
	DLESS,
	DLESSDASH,
	GREATAND,
	LESSAND,
	LESSANDDASH,
	GREATANDDASH,
}				t_token_type;

typedef enum	e_error
{
	EACCESS = 1,
	ECMDNOTFOUND,
	ENOTFOUND,
	ENOTDIR,
	ENAMETOOLONG,
	ENOHOME,
	ENOOLPPWD,
	EPATHISDIR,
	EREDIRECTION,
	EAMBIGREDIRECT,
	ESYNTAX,
	EUNK
}				t_error;

typedef enum	e_command_type
{
	SIMPLE_CMD = 1,
	PIPE_SEQ
}				t_command_type;

typedef struct	s_token
{
	t_token_type	type;
	void			*data;
}				t_token;

typedef struct	s_command
{
	t_vector		*tokens;
	t_vector		*here_docs;
	t_command_type	type;
}				t_command;

typedef struct	s_env_var
{
	char	*key;
	char	*value;
}				t_env_var;

typedef struct	s_here_doc
{
	int		pipe_fd;
	int		fd;
}				t_here_doc;

#endif
