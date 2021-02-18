/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagtab <ylagtab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 19:05:18 by ylagtab           #+#    #+#             */
/*   Updated: 2021/02/18 19:05:29 by ylagtab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "internal.h"

void	redirect_input(t_redirect_input_info *redirect_input_info)
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
