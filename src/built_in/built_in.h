/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagtab <ylagtab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/22 00:27:21 by vanderwolk        #+#    #+#             */
/*   Updated: 2021/02/12 11:03:39 by ylagtab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILT_IN_H
# define BUILT_IN_H

typedef struct	s_env_var
{
	char	*key;
	char	*value;
}				t_env_var;

int				run_built_in(t_vector *mini_env, char **args, size_t args_len);
void			cd(t_vector *mini_env, char **args, size_t args_len);
void			pwd(size_t args_len);
void			echo(char **args);
void			env(t_vector *mini_env, char **args, size_t args_len);
void			env_set(t_vector *mini_env, char **args, size_t args_len);
void			env_unset(t_vector *mini_env, char **args, size_t args_len);
t_vector		*env_init(char **envp);
char			**mini_env_to_envp(t_vector *mini_env);
char			*env_get(t_vector *mini_env, char *key);
void			env_add(t_vector *mini_env, char *key, char *value);
void			env_remove(t_vector *mini_env, char *key);
int				is_env_var(char *str, size_t i);
void			exit_shell(char **args, size_t args_len);
void			free_env_var(void *content, size_t content_size);
char			*join_paths(char *path1, char *path2);

#endif
