/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagtab <ylagtab@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/08 09:49:50 by ylagtab           #+#    #+#             */
/*   Updated: 2021/03/12 11:32:32 by ylagtab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# define SINGLE_QUOTE '\''
# define DOUBLE_QUOTE '"'
# define BACK_SLASH '\\'

t_vector	*parse_command(char *cmd);
char		quote_type(char c);
int			is_space(char c, int quote);
void		remove_quotes(t_vector *tokens);
char		*remove_quotes_from_word(char *word);

#endif
