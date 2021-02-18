/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagtab <ylagtab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/14 17:18:11 by ylagtab           #+#    #+#             */
/*   Updated: 2021/02/18 14:41:27 by ylagtab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "internal.h"

static void	check_output_file_errors(char *filename)
{
	struct stat st;

	g_errno = 0;
	if (stat(filename, &st) == -1)
		g_errno = EUNK;
	if (S_ISDIR(st.st_mode))
		g_errno = EPATHISDIR;
	else if (access(filename, W_OK) == -1)
		g_errno = EACCESS;
}

static int	open_file(t_redirect_input_info *redirect_input_info)
{
	int	file_fd;
	int	write_mode;

	write_mode = redirect_input_info->append == TRUE ?
		O_APPEND : O_WRONLY | O_CREAT;
	file_fd = open(redirect_input_info->file_pathname, write_mode, UMASK);
	check_output_file_errors(redirect_input_info->file_pathname);
	return (file_fd);
}

static void	redirect_input(t_redirect_input_info *redirect_input_info)
{
	int	file_fd;

	file_fd = open_file(redirect_input_info);
	if (file_fd < 0)
		ft_perror(redirect_input_info->file_pathname, NULL, TRUE);
	if (dup2(file_fd, redirect_input_info->fd) == -1)
	{
		g_errno = EREDIRECTION;
		ft_perror(NULL, NULL, TRUE);
	}
}

static void	remove_redirections_tokens(t_vector *tokens)
{
	t_token	*tk;
	size_t	i;

	i = 0;
	while (i < tokens->length)
	{
		tk = (t_token*)tokens->array[i]->content;
		if (tk->type > PIPELINE)
		{
			ft_vector_remove_at(tokens, i, delete_token);
			if (tk->type != GREATANDDASH)
				ft_vector_remove_at(tokens, i, delete_token);
		}
		else
			++i;
	}
}

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
