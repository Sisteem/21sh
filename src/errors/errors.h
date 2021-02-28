/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagtab <ylagtab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 09:55:34 by ylagtab           #+#    #+#             */
/*   Updated: 2021/02/18 12:14:31 by ylagtab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H
# define ERRORS_H

extern t_error	g_errno;

void			ft_perror(char *prefix, char *suffix, t_bool exit_on_error);
void			ft_strerror(t_error e, char *prefix, char *suffix,
					t_bool exit_on_error);

#endif
