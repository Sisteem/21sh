/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   internal.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagtab <ylagtab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 18:52:14 by ylagtab           #+#    #+#             */
/*   Updated: 2021/02/18 19:10:04 by ylagtab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INETRNAL_H
# define INETRNAL_H

# include "twenty_one.h"

# define UMASK 0644

typedef struct	s_redirect_input_info
{
	char	*file_pathname;
	int		fd;
	t_bool	append;
}				t_redirect_input_info;

int				open_file(t_redirect_input_info *redirect_input_info);
void			remove_redirections_tokens(t_vector *tokens);
void			redirect_input(t_redirect_input_info *redirect_input_info);

#endif
