/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocgraf <ocgraf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 15:58:14 by ocgraf            #+#    #+#             */
/*   Updated: 2025/08/24 11:53:12 by ocgraf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# include "../libft/libft.h"
# include "builtin.h"
# include "parsing.h"
# include "struct.h"

// args.c
/**
 * @brief Join an array of arguments into a single string. Free the input array.
 * @param[in] args Array of arguments.
 * @return  Joined string of arguments. NULL on failure.
 */
char	*join_args(char **args);
/**
 * @brief Count the number of arguments in an array.
 * @param[in] args Array of arguments.
 * @return Number of arguments.
 */
int		args_count(char **args);

// exec.c
int		is_builtin(t_cmd *cmd);
int		exec_function(t_cmd *cmd, t_env *env);

// env_to_array.c
/**
 * @brief Get the size of the list of environment variables.
 * @param[in] env Head of list.
 * @return The number of environment variables in the list.
 */
int		env_size(t_env *env);
/**
 * @brief Convert environment variables list to an array of strings.
 * @param[in, out] env The head of the linked list of environment variables.
 * @return A NULL-terminated array in the format "NAME=VALUE".
*/
char	**env_to_array(t_env *env);
/**
 * @brief Add each directory in PATH to the command name.
 * @param[in, out] path Array of directories in PATH.
 * @param[in] cmd Command structure.
*/
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