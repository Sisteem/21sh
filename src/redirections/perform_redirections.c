/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perform_redirections.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagtab <ylagtab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/14 17:18:11 by ylagtab           #+#    #+#             */
/*   Updated: 2021/03/05 19:34:51 by ylagtab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "internal.h"

static int	check_ambiguous_redirect(char *str)
{
	if (str == NULL || *str == '\0')
	{
		g_errno = EAMBIGREDIRECT;
		ft_perror(NULL, NULL, FALSE);
		return (-1);
	}
	return (0);
}

static int	is_redirection(t_token_type type)
{
	return (
		type == GREAT ||
		type == DGREAT ||
		type == ANDGREAT ||
		type == ANDDGREAT ||
		type == LESS ||
		type == DLESS ||
		type == DLESSDASH ||
		type == GREATAND);
}

static int	handle_redirections(int io_number, t_token_type tk_type, void *word)
{
	int err;

	err = EXIT_SUCCESS;
	if (check_ambiguous_redirect(word) == -1)
		return (-1);
	if (tk_type == GREAT || tk_type == DGREAT)
		err = redirect_output(word, io_number, tk_type == DGREAT);
	else if (tk_type == ANDGREAT || tk_type == ANDDGREAT)
	{
		err = redirect_output(word, STDOUT_FILENO, tk_type == ANDDGREAT);
		if (err == EXIT_SUCCESS)
			err = fd_aggregation(STDOUT_FILENO, STDERR_FILENO);
	}
	else if (tk_type == GREATAND)
		err = fd_aggregation(ft_atoi(word), io_number);
	else if (tk_type == LESS)
		err = redirect_input(word, io_number);
	else if (tk_type == DLESS || tk_type == DLESSDASH)
		err = here_document(io_number, word, tk_type == DLESSDASH);
	if (err == -1)
		ft_perror(g_errno != EREDIRECTION ? word : NULL, NULL, FALSE);
	return (err);
}

int			perform_redirections(t_vector *tokens)
{
	t_token	*tk;
	t_token	*tmp_tk;
	int		io_number;
	size_t	i;

	i = 0;
	io_number = -1;
	while (i < tokens->length)
	{
		tk = (t_token*)tokens->array[i]->content;
		if (tk->type == IO_NUMBER)
			io_number = *(int*)tk->data;
		else if (is_redirection(tk->type))
		{
			tmp_tk = (t_token*)tokens->array[i + 1]->content;
			if (handle_redirections(io_number, tk->type, tmp_tk->data) == -1)
				return (-1);
		}
		else if (tk->type == GREATANDDASH)
			close_output(io_number);
		++i;
	}
	remove_redirections_tokens(tokens);
	return (EXIT_SUCCESS);
}
