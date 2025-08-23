/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocgraf <ocgraf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 12:44:28 by ocgraf            #+#    #+#             */
/*   Updated: 2025/08/23 15:59:44 by ocgraf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H
# include "minishell.h"

//	cd.c
/*
* @brief Change the current working directory.
* @param[in] args Array of arguments.
* @return 0 on success, 1 on failure.
*/
int		mini_cd(char **args, t_env *env);

//	echo.c
/*
* @brief Print the arguments to the standard output.
* @param[in] args Array of arguments.
*/
void	mini_echo(char **prompt);
/*
* @brief Print the arguments to the standard output.
* @param[in] args Array of arguments.
*/
int		disable_nl(char *prompt);

//	env.c
int		mini_env(t_env *env);

//	exit.c
int		mini_exit(int exit_code);

//	export.c
int		mini_export(t_env *env, char **args);
int		mini_export2(t_env *env, char *name, char *value);
t_env	*insert_env(t_env *env, char *name, char *value);

//	pwd.c
int		mini_pwd(void);

//	unset.c
int		mini_unset(t_env *env, char **args);
#endif