/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocgraf <ocgraf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 15:58:14 by ocgraf            #+#    #+#             */
/*   Updated: 2025/08/23 16:00:29 by ocgraf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H
# include "minishell.h"

// args.c
char	*join_args(char **args);
int		args_count(char **args);

// exec.c
bool	is_builtin(t_cmd *cmd);
int		exec_function(t_cmd *cmd, t_env *env);

int		env_size(t_env *env);
char	**env_to_array(t_env *env);
char	**path_to_array(char **path, t_cmd *cmd);

// free.c
void	double_free(void **ptr);

// env.c
t_env	*get_env(char **envp);
t_env	*create_env(char *name, char *value);
t_env	*add_env_back(t_env *env, char *name, char *value);
void	free_env(t_env *env);
void	modify_env(t_env *env, char *name, char *value);

void	delete_env(t_env *to_delete, t_env *head);
void	delete_all_env(t_env *head);
t_env	*search_env(t_env *head, const char *name);
t_env	*add_env(t_env *current_env, t_env *to_add);

#endif