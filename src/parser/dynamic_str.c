/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dynamic_str.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagtab <ylagtab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 09:54:26 by ylagtab           #+#    #+#             */
/*   Updated: 2021/03/10 10:14:47 by ylagtab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "internal.h"

t_dynamic_str	*dynamic_str_new(void)
{
	t_dynamic_str	*ptr;

	ptr = (t_dynamic_str*)ft_malloc(sizeof(t_dynamic_str));
	ptr->capacity = 1024;
	ptr->length = 0;
	ptr->data = (char*)ft_malloc(ptr->capacity);
	return (ptr);
}

void			dynamic_str_free(t_dynamic_str *dyn_str)
{
	free(dyn_str->data);
	free(dyn_str);
}

void			dynamic_str_push(t_dynamic_str *dyn_str, char c)
{
	char	*s;

	if (dyn_str->length == dyn_str->capacity)
	{
		s = ft_realloc(dyn_str->data, dyn_str->capacity, dyn_str->capacity * 2);
		dyn_str->capacity *= 2;
		free(dyn_str->data);
		dyn_str->data = s;
	}
	dyn_str->data[dyn_str->length] = c;
	++(dyn_str->length);
}
