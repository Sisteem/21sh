/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagtab <ylagtab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/22 00:27:21 by vanderwolk        #+#    #+#             */
/*   Updated: 2021/02/24 16:37:10 by ylagtab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILT_IN_H
# define BUILT_IN_H

int			is_built_in(char *str);
int			run_built_in(char **args, size_t args_len);
int			cd(char **args, size_t args_len);
int			pwd(size_t args_len);
int			echo(char **args);
int			env(char **args, size_t args_len);
int			env_set(char **args, size_t args_len);
int			env_unset(char **args, size_t args_len);
t_vector	*env_init(char **envp);
char		**shell_env_to_envp(t_vector *sehll_env);
char		*env_get(char *key);
void		env_add(char *key, char *value);
void		env_remove(char *key);
int			is_env_var(char *str, size_t i);
int			exit_shell(char **args, size_t args_len);
void		free_env_var(void *content, size_t content_size);
char		*join_paths(char *path1, char *path2);

#endif
