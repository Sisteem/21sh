/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   internal.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-idri <mel-idri@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 16:04:46 by ylagtab           #+#    #+#             */
/*   Updated: 2021/03/15 15:39:53 by mel-idri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERNAL_H
# define INTERNAL_H

# include "twenty_one.h"

void		set_env_var(char *name, char *value);
void		run_env(char **args, size_t utility_index);
void		reset_env(t_vector *tmp_shell_env);
t_vector	*env_dup(t_vector *env);

#endif
