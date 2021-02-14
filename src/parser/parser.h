/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagtab <ylagtab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/08 09:49:50 by ylagtab           #+#    #+#             */
/*   Updated: 2021/02/13 20:00:01 by ylagtab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# define SINGLE_QUOTE '\''
# define DOUBLE_QUOTE '"'
# define BACK_SLASH '\\'

typedef enum	e_token_type
{
	NONE,
	WORD,
	IO_NUMBER,
	SEMI,
	PIPELINE,
	DLESSDASH,
	DLESS,
	LESS,
	ANDDGREAT,
	ANDGREAT,
	DGREAT,
	GREATANDDASH,
	GREATAND,
	GREAT,
	NEWLINE
}				t_token_type;

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
	t_command_type	type;
}				t_command;

t_vector		*parse_command(char *cmd);
char			quote_type(char c);
int				is_space(char c, int quote);

#endif
