/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perform_redirections.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagtab <ylagtab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/14 17:18:11 by ylagtab           #+#    #+#             */
/*   Updated: 2021/02/18 19:09:01 by ylagtab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "internal.h"

void		perform_redirections(t_vector *tokens)
{
	t_redirect_input_info	redirect_input_info;
	t_token					*tk;
	size_t					i;

	i = 0;
	redirect_input_info.fd = -1;
	while (i < tokens->length)
	{
		tk = (t_token*)tokens->array[i]->content;
		if (tk->type == IO_NUMBER)
			redirect_input_info.fd = *(int*)tk->data;
		if (tk->type == GREAT || tk->type == DGREAT)
		{
			if (redirect_input_info.fd == -1)
				redirect_input_info.fd = STDOUT_FILENO;
			redirect_input_info.append = tk->type == DGREAT;
			tk = (t_token*)tokens->array[i + 1]->content;
			redirect_input_info.file_pathname = tk->data;
			redirect_input(&redirect_input_info);
		}
		++i;
	}
	remove_redirections_tokens(tokens);
}
