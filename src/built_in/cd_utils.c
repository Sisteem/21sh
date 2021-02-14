/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagtab <ylagtab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 18:56:43 by ylagtab           #+#    #+#             */
/*   Updated: 2021/02/13 18:20:05 by ylagtab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one.h"

static t_vector	*strings_array_to_vector(char **arr)
{
	t_vector	*vec;
	char		*tmp;
	size_t		i;

	vec = ft_vector_new_capacity(ft_strings_array_length(arr));
	i = 0;
	while (arr[i] != NULL)
	{
		tmp = ft_strdup(arr[i]);
		ft_vector_add(vec, &tmp, sizeof(char*));
		++i;
	}
	return (vec);
}

static char		*vector_join_strings(t_vector *vec)
{
	char	*res;
	size_t	i;

	i = 0;
	res = ft_strdup("/");
	while (i < vec->length)
	{
		res = ft_strjoin_free(res, *(char**)vec->array[i]->content, 1, 1);
		if (i < vec->length - 1)
			res = ft_strjoin_free(res, "/", 1, 0);
		free(vec->array[i]->content);
		free(vec->array[i]);
		vec->array[i] = NULL;
		++i;
	}
	free(vec->array);
	free(vec);
	return (res);
}

static void		free_entry(void *content, size_t content_size)
{
	(void)content_size;
	free(*(char**)content);
	free(content);
}

char			*join_paths(char *path1, char *path2)
{
	t_vector	*res_path;
	char		**path1_parts;
	char		**path2_parts;
	char		*tmp;
	size_t		i;

	path1_parts = ft_strsplit(path1, '/');
	path2_parts = ft_strsplit(path2, '/');
	res_path = strings_array_to_vector(path1_parts);
	i = 0;
	while (path2_parts[i] != NULL)
	{
		if (ft_strequ(path2_parts[i], "..") && res_path->length > 0)
			ft_vector_remove_at(res_path, res_path->length - 1, free_entry);
		else if (!ft_strequ(path2_parts[i], ".") &&
			!ft_strequ(path2_parts[i], ".."))
		{
			tmp = ft_strdup(path2_parts[i]);
			ft_vector_add(res_path, &tmp, sizeof(char*));
		}
		++i;
	}
	ft_free_strings_array(path1_parts);
	ft_free_strings_array(path2_parts);
	return (vector_join_strings(res_path));
}
