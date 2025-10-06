/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljudd <ljudd@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 12:44:28 by ocgraf            #+#    #+#             */
/*   Updated: 2025/10/06 11:00:39 by ljudd            ###   ########.fr       */
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
# include "struct.h"

//	cd.c
/**
 * @brief Check if required environment variables for cd are set.
 * @param[in] env Environment variables list.
 * @param[out] pwd Pointer to PWD environment variable.
 * @param[out] old_pwd Pointer to OLDPWD environment variable.
 * @param[out] home Pointer to HOME environment variable.
 * @return 0 on success, -1 if any required variable is not set.
 */
int		check_cd_env(t_env *env, t_env **pwd, t_env **old_pwd, t_env **home);
/**
 * @brief Change to the specified directory.
 * @param[in] args Array of arguments (directory path or ~ for HOME).
 * @param[in] home_env HOME environment variable.
 * @return 0 on success, 1 on error.
 */
int		change_directory(char **args, t_env *home_env);
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
 * @return 0 on success.
*/
int		mini_echo(char **args);

//	env.c
/**
 * @brief Print all environment variables.
 * @param[in] env Environment variables list.
 * @return 0 on success.
*/
int		mini_env(t_env *env);

//	exit.c
/**
 * @brief Free all allocated memory and exit the program.
 * 
 * @param[in] data Data structure containing all allocated memory to free.
 * @param[in] exit_code Exit code of the program.
 * 12 = MALLOC ERROR
 * 11 = ERROR PARSING EXIT CODE
 * 8 = parsing missing closing quote
 */
void	clean_exit(t_data *data, int exit_code);
/**
 * @brief Exit the shell with an exit code.
 * @param[in] args Array of arguments (optional exit code).
 * @param[in] data Data structure for clean exit.
 * @return 0 on success, 1 on error (invalid exit code).
*/
int		mini_exit(char **args, t_data *data);

//	export.c
/**
 * @brief Export environment variables.
 * @param[in, out] env Environment variables list.
 * @param[in] args Array of arguments in format "NAME=VALUE".
 * @return 0 on success, 1 on error.
*/
int		mini_export(t_env *env, char **args);
/**
 * @brief Export a single environment variable.
 * @param[in, out] env Environment variables list.
 * @param[in] name Variable name (will be freed by function).
 * @param[in] value Variable value (will be freed by function).
 * @return 0 on success, 1 on error.
*/
int		mini_export2(t_env *env, char *name, char *value);
/**
 * @brief Insert a new environment variable in sorted order.
 * @param[in] env Environment variables list.
 * @param[in] name Variable name.
 * @param[in] value Variable value.
 * @return Pointer to the new environment variable, NULL on error.
*/
t_env	*insert_env(t_env *env, char *name, char *value);
/**
 * @brief Check if a string is a valid identifier for environment variables.
 * @param[in] name String to check.
 * @return 1 if valid, 0 otherwise.
*/
int		is_valid_identifier(char *name);
/**
 * @brief Process a single export argument.
 * @param[in, out] env Environment variables list.
 * @param[in] arg Argument to process.
 * @param[in, out] has_error Error flag to update.
 * @return 0 on success, 1 on fatal error.
*/
int		process_export_arg(t_env *env, char *arg, int *has_error);
/**
 * @brief Process export with value assignment.
 * @param[in, out] env Environment variables list.
 * @param[in] arg Full argument string.
 * @param[in] equal Pointer to '=' character in arg.
 * @param[in, out] has_error Error flag to update.
 * @return 0 on success, 1 on fatal error.
*/
int		export_with_value(t_env *env, char *arg, char *equal, int *has_error);

//	pwd.c
/**
 * @brief Print the current working directory.
 * @return 0 on success, 1 on error.
*/
int		mini_pwd(void);

//	unset.c
/**
 * @brief Unset environment variables.
 * @param[in, out] env Environment variables list.
 * @param[in] args Array of variable names to unset.
 * @return 0 on success, 1 on error.
*/
int		mini_unset(t_env *env, char **args);
#endif