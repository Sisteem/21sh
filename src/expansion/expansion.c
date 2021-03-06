/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-idri <mel-idri@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 15:33:44 by ylagtab           #+#    #+#             */
/*   Updated: 2021/03/13 15:22:49 by mel-idri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "internal.h"

static void	expand_command(t_vector *tokens)
{
	t_token			*tk;
	char			*word;
	t_token_type	old_token_type;
	t_token_type	current_token_type;
	size_t			i;

	i = 0;
	old_token_type = NONE;
	while (i < tokens->length)
	{
		tk = (t_token*)tokens->array[i]->content;
		current_token_type = tk->type;
		if (current_token_type == WORD &&
			old_token_type != DLESS && old_token_type != DLESSDASH)
		{
			word = expand_word(tk->data, FALSE);
			free(tk->data);
			tk->data = ft_strtrim(word);
			free(word);
			tokens_to_fileds(tokens, &i);
		}
		old_token_type = current_token_type;
		++i;
	}
}

char		*expand_here_doc_buffer(char *buffer)
{
	char	*res;

	res = expand_word(buffer, TRUE);
	free(buffer);
	buffer = remove_quotes_from_word(res);
	free(res);
	return (buffer);
}

void		expansion(t_vector *commands)
{
	t_command	*cmd;
	size_t		i;

	i = 0;
	while (i < commands->length)
	{
		cmd = (t_command*)commands->array[i]->content;
		expand_command(cmd->tokens);
		++i;
	}
}
