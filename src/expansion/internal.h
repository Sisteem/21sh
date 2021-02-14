/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   internal.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagtab <ylagtab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 15:35:16 by ylagtab           #+#    #+#             */
/*   Updated: 2021/02/13 19:54:11 by ylagtab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERNAL_H
# define INTERNAL_H

# include "twenty_one.h"

char	*expand_word(char *word);
int		is_tilde(char *word, size_t i);
int		is_env_var(char *word, size_t i);
char	*expand_tilde(char *word, char *result, size_t *end, size_t *start);
char	*expand_env_var(char *word, char *result, size_t *end, size_t *start);
void	tokens_to_fileds(t_vector *tokens, size_t *index);

#endif
