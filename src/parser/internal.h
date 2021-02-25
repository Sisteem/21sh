/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   internal.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagtab <ylagtab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 09:53:22 by ylagtab           #+#    #+#             */
/*   Updated: 2021/02/25 11:34:13 by ylagtab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERNAL_H
# define INTERNAL_H

# include "twenty_one.h"

/*
** Type definitions
*/

typedef struct	s_tokenization
{
	char			token[4096];
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

#endif
