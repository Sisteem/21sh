/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   internal.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-idri <mel-idri@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 18:52:14 by ylagtab           #+#    #+#             */
/*   Updated: 2021/03/14 10:24:09 by mel-idri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERNAL_H
# define INTERNAL_H

# include "twenty_one.h"

# define UMASK 0644
# define REDI_OUT 0
# define REDI_IN 1

typedef	struct	s_delimiter
{
	char	*str;
	t_bool	is_quoted;
}				t_delimiter;

void			remove_redirections_tokens(t_vector *tokens);
int				redirect_output(char *filename, int io_number, t_bool append);
int				redirect_input(char *filename, int io_number);
int				fd_aggregation(int io_number, t_token_type type, char *word);
void			close_fd(int io_number, int redi_type);
int				here_document(t_vector *here_docs, size_t *index);
int				create_buffer_pipe(t_command *cmd, int fd, t_delimiter *delim,
					t_bool remove_tabs);
void			free_delimiter(t_delimiter *delim);
t_delimiter		*get_delimiter(t_token *tk);
int				get_redirect_fd(t_vector *tokens, size_t i);

#endif
