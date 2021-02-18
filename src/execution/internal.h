/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   internal.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagtab <ylagtab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/14 17:11:27 by ylagtab           #+#    #+#             */
/*   Updated: 2021/02/18 12:32:11 by ylagtab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERNAL_H
# define INTERNAL_H

# include "twenty_one.h"

# define UMASK 0644

typedef struct	s_redirect_input_info
{
	char	*file_pathname;
	int		fd;
	t_bool	append;
}				t_redirect_input_info;

void			perform_redirections(t_vector *tokens);

#endif
