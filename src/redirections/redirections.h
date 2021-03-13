/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagtab <ylagtab@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 18:52:40 by ylagtab           #+#    #+#             */
/*   Updated: 2021/03/13 10:54:17 by ylagtab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIRECTIONS_H
# define REDIRECTIONS_H

int		perform_redirections(t_command *cmd);
int		prepare_cmd_here_docs(t_command *cmd);
int		prepare_commands_here_docs(t_vector *commands);

#endif
