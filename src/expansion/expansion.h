/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-idri <mel-idri@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 15:33:47 by ylagtab           #+#    #+#             */
/*   Updated: 2021/03/13 15:22:58 by mel-idri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSION_H
# define EXPANSION_H

void	expansion(t_vector *commands);
char	*expand_word(char *word, t_bool is_here_doc);
char	*expand_here_doc_buffer(char *buffer);

#endif
