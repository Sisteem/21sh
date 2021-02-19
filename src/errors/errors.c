/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagtab <ylagtab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 10:01:19 by ylagtab           #+#    #+#             */
/*   Updated: 2021/02/19 11:51:24 by ylagtab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "internal.h"

t_error		g_errno;

const char	*g_error_message_string[] = {
	"",
	"Permission denied",
	"Command not found",
	"No such file or directory",
	"Not a directory",
	"File name too long",
	"HOME not set",
	"OLDPWD not set",
	"is a directory",
	"Redirection error",
	"ambiguous redirect",
	"An error has occured"
};

void	ft_perror(char *prefix, char *suffix, t_bool exit_on_error)
{
	if (g_errno > EUNK)
		g_errno = EUNK;
	ft_printf(2, "21sh: ");
	if (prefix != NULL)
		ft_printf(2, "%s: ", prefix);
	ft_printf(2, "%s", g_error_message_string[g_errno]);
	if (suffix != NULL)
		ft_printf(2, " %s", suffix);
	ft_printf(1, "\n");
	if (g_errno > 0 && exit_on_error == TRUE)
		exit(g_errno);
}

void	ft_strerror(t_error e, char *prefix, char *suffix, t_bool exit_on_error)
{
	t_error	tmp_err;

	tmp_err = g_errno;
	g_errno = e;
	ft_perror(prefix, suffix, exit_on_error);
	g_errno = tmp_err;
}
