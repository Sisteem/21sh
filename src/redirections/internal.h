/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   internal.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagtab <ylagtab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 18:52:14 by ylagtab           #+#    #+#             */
/*   Updated: 2021/02/21 08:46:09 by ylagtab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INETRNAL_H
# define INETRNAL_H

# include "twenty_one.h"

# define UMASK 0644

void			remove_redirections_tokens(t_vector *tokens);
void			redirect_output(char *filename, int io_number, t_bool append);
void			redirect_input(char *filename, int io_number);
void			fd_aggregation(int old_fd, int new_fd);
void			here_document(int fd, char *delimeter);

#endif
