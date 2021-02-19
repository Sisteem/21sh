/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perform_redirections.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagtab <ylagtab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/14 17:18:11 by ylagtab           #+#    #+#             */
/*   Updated: 2021/02/19 08:06:09 by ylagtab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "internal.h"

void		perform_redirections(t_vector *tokens)
{
	t_token	*tk;
	int		io_number;
	size_t	i;

	i = 0;
	io_number = -1;
	while (i < tokens->length)
	{
		tk = (t_token*)tokens->array[i]->content;
		if (tk->type == IO_NUMBER)
			io_number = *(int*)tk->data;
		else if (tk->type == GREAT || tk->type == DGREAT)
		{
			if (io_number == -1)
				io_number = STDOUT_FILENO;
			tk = (t_token*)tokens->array[i + 1]->content;
			redirect_output(tk->data, io_number, tk->type == DGREAT);
		}
		else if (tk->type == LESS)
		{
			if (io_number == -1)
				io_number = STDIN_FILENO;
			tk = (t_token*)tokens->array[i + 1]->content;
			redirect_input(tk->data, io_number);
		}
		++i;
	}
	remove_redirections_tokens(tokens);
}
