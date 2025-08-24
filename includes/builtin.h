/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocgraf <ocgraf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 12:44:28 by ocgraf            #+#    #+#             */
/*   Updated: 2025/08/24 15:45:34 by ocgraf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

/**
 * @file builtin.h
 * @brief Built-in shell commands.
 * @note Some functions does not execute in child process. (cd, exit, export
 * unset).
 * @return 0 on success, 1 on user error, -1 on system error.
 * -1 implies that the program should exit properly.
 */

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# include "../libft/libft.h"
# include "exec.h"
# include "parsing.h"
# include "struct.h"

//	cd.c
/**
 * @brief Change the current working directory.
 * @param[in] args Array of arguments.
 * @return 0 on success, 1 on user error, -1 on system error.
*/
int		mini_cd(char **args, t_env *env);

//	echo.c
/**
 * @brief Print the arguments to the standard output.
 * @param[in] args Array of arguments.
*/
void	mini_echo(char **prompt);
/**
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