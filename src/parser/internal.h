/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   internal.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagtab <ylagtab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 09:53:22 by ylagtab           #+#    #+#             */
/*   Updated: 2021/03/10 10:12:29 by ylagtab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERNAL_H
# define INTERNAL_H

# include "twenty_one.h"

/*
** Type definitions
*/

typedef struct	s_dynamic_str
{
	char	*data;
	size_t	length;
	size_t	capacity;
}				t_dynamic_str;

typedef struct	s_tokenization
{
	t_dynamic_str	*token;
	t_vector		*tokens_list;
	int				t_index;
	t_token_type	token_type;
	char			quote;
}				t_tokenization;

typedef struct	s_construct_commands
{
	t_vector		*commands;
	t_token			*token;
	size_t			i;
	size_t			j;
	t_command_type	cmd_type;
}				t_construct_commands;

typedef struct	s_remove_quotes
{
	char	str[BUFF_SIZE];
	int		s_index;
	int		w_index;
	char	quote;
	t_bool	backslash;
}				t_remove_quotes;

/*
** Functions Prototypes
*/

t_vector		*tokenization(char *args_line);
t_vector		*construct_commands(t_vector *tokens);
int				syntax_analys(t_vector *tokens);
int				is_word(char c, int quote);
int				is_number(char c, int quote);
int				is_operator(char c, int quote);
t_token_type	fill_operator(char **str, t_tokenization *t);
t_dynamic_str	*dynamic_str_new(void);
void			dynamic_str_free(t_dynamic_str *dyn_str);
void			dynamic_str_push(t_dynamic_str *dyn_str, char c);

#endif
