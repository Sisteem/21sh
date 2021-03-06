/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_command_line.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagtab <ylagtab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 18:17:19 by ylagtab           #+#    #+#             */
/*   Updated: 2021/03/10 19:28:18 by ylagtab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one.h"

static int	is_quote(char c)
{
	if (c == DOUBLE_QUOTE || c == SINGLE_QUOTE)
		return (c);
	return (0);
}

static void	remove_ending_backslash(char **cmd)
{
	size_t	cmd_len;

	cmd_len = ft_strlen(*cmd);
	if ((*cmd)[cmd_len - 1] == BACK_SLASH)
	{
		(*cmd)[cmd_len - 1] = '\0';
		return ;
	}
	*cmd = ft_strjoin_free(*cmd, "\n", 1, 0);
}

static char	*trim_spaces(char *cmd)
{
	char *tmp;

	if (*cmd == '\0')
		return (cmd);
	tmp = cmd;
	cmd = ft_strtrim(cmd);
	free(tmp);
	return (cmd);
}

static int	check_quotes_backslashes(char *str)
{
	int		i;
	int		valid;
	int		backslash;
	char	quote;

	i = 0;
	quote = 0;
	valid = 1;
	backslash = 0;
	while (str[i])
	{
		if (quote && quote == is_quote(str[i]) && !backslash)
		{
			quote = 0;
			valid = 1;
		}
		else if (!quote && is_quote(str[i]) && !backslash)
		{
			quote = is_quote(str[i]);
			valid = 0;
		}
		backslash = !backslash && str[i] == BACK_SLASH && quote != SINGLE_QUOTE;
		i++;
	}
	return (valid && !backslash);
}

int			read_command_line(char **cmd)
{
	char	*prompt;
	char	*line;
	int		ret;

	if (cmd == NULL)
		return (ERROR);
	*cmd = ft_strdup("");
	prompt = PS1;
	while (1)
	{
		if ((ret = readline_21sh(&line, prompt)) != LINE)
		{
			ft_memdel((void**)cmd);
			return (ret);
		}
		*cmd = ft_strjoin_free(*cmd, line, 1, 1);
		if (check_quotes_backslashes(*cmd))
			break ;
		remove_ending_backslash(cmd);
		prompt = PS2;
	}
	if ((*cmd)[0] != ' ' && (*cmd)[0] != '\0')
		add_hist_entry(*cmd);
	*cmd = trim_spaces(*cmd);
	return (LINE);
}
