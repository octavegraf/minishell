/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocgraf <ocgraf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 15:58:14 by ocgraf            #+#    #+#             */
/*   Updated: 2025/09/29 16:49:26 by ocgraf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>

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
/**
 * @brief Check if a command is a built-in shell command.
 * 
 * @param[in] cmd String of the command to check.
 * @return 1 if the command is executed in parent, 2 if executed in child,
 * otherwise 0.
 */
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

// exec.c
/**
 * @brief Execute a built-in command.
 * 
 * @param[in] cmd Command structure.
 * @param[in] env Environment variables structures.
 * @return int 0 on success, 1 on failure.
 */
int		exec_builtin(t_cmd *cmd, t_env *env);
/**
 * @brief Execute an external command.
 * 
 * @param[in] cmd Command structure.
 * @param[in] env Environment variables structures.
 * @return int 0 on success, 1 on failure.
 */
int		exec_external(t_cmd *cmd, t_env *env);
/**
 * @brief Execute a command in a child process.
 * 
 * @param[in] cmd Command structure.
 * @param[in] env Environment variables structures.
 * @return int 0 on success, 1 on failure.
 */
int		exec_in_child(t_cmd *cmd, t_env *env);
/**
 * @brief Decide between built-in or external command and execute it.
 * It will not create a new process.
 * 
 * @param[in] cmd Command structure.
 * @param[in] env Environment variables structures.
 * @return int 0 on success, 1 on failure.
 */
int		exec_function(t_cmd *cmd, t_env *env);
/**
 * @brief Decide if a command should be executed in the parent or child process
 * then execute it.
 * 
 * @param[in] cmd Command structure.
 * @param[in] env Environment variables structures.
 * @return int 0 on success, 1 on failure.
 */
int		exec_decide(t_cmd *cmd, t_env *env);

// env.c
t_env	*get_env(char **envp);
t_env	*create_env(char *name, char *value);
t_env	*add_env_back(t_env *env, char *name, char *value);
void	free_env(t_env *env);
/**
 * @brief Modify an environment variable.
 * @note Only modifies the name or the value if they are not NULL.
 * @param[in, out] env Head of the environment variable list.
 * @param[in] name Name of the environment variable to modify.
 * @param[in] value New value for the environment variable.
 * @return 0 on success, 1 on failure.
 */
int		modify_env(t_env *env, char *name, char *value);

void	delete_env(t_env *to_delete, t_env *head);
void	delete_all_env(t_env *head);
/**
 * @brief Search for an environment variable by name.
 * @param[in] head Head of the environment variable list.
 * @param[in] name Name of the environment variable to search for.
 * @return Pointer to the found environment variable, or NULL if not found.
 */
t_env	*search_env(t_env *head, const char *name);
t_env	*add_env(t_env *current_env, t_env *to_add);

// pipes.c
/**
 * @brief Setup child objects for a command in a pipeline.
 * 
 * @param cmd Command structure.
 * @param prev_pipefd File descriptor for the previous pipe.
 * @param pipefd Array to hold the current pipe file descriptors.
 * @param env Environment variables structures.
 */
void	setup_child(t_cmd *cmd, int prev_pipefd, int *pipefd, t_env *env);
/**
 * @brief Close the pipes for a command in a pipeline.
 * 
 * @param prev_pipefd File descriptor for the previous pipe.
 * @param pipefd Array to hold the current pipe file descriptors.
 * @param cmd Command structure.
 */
void	close_parent_pipes(t_cmd *cmd, int *prev_pipefd, int *pipefd);
/**
 * @brief Execute a pipeline of commands.
 * 
 * @param[in] cmd First command in the pipeline.
 * @param[in] env Environment variables structures.
 * @param[in] count Dummy value (will be overwritten).
 * @return int 0 on success, 1 on failure.
 */
int		exec_pipeline(t_cmd *cmd, t_env *env);

// redirs.c
/**
 * @brief Open a file for output redirection.
 * 
 * @param[in] redir Redirection structure.
 * @param[in] append 1 to append to the file, 0 to truncate.
 * @return int File descriptor on success, -1 on failure.
 */
int		open_redir_out(t_redir *redir, int append);
/**
 * @brief Open a file for input redirection.
 * 
 * @param[in] redir Redirection structure.
 * @return int File descriptor on success, -1 on failure.
 */
int		open_redir_in(t_redir *redir);
/**
 * @brief Create a heredoc.
 * 
 * @note The end delimiter will work only if it match the complete string.
 * @param[in] end The end delimiter.
 * @return int The STDIN file descriptor on success, -1 on failure.
 */
int		create_heredoc(const char *end, t_env *env);
/**
 * @brief Apply all redirections for a command.
 * @note Due to 42 norm, dummy values are used. You can pass whatever you want.
 * @param redirs Redirection structure.
 * @param fd Dummy value (will be overwritten).
 * @param dup_result Dummy value (will be overwritten).
 * @return int 0 on success, 1 on failure.
 */
/**
 * @brief Apply redirections for a command.
 * 
 * @param[in] redirs List of redirections to apply.
 * @param[in] fd File descriptor (unused in current implementation).
 * @param[in] dup_result Dup result (unused in current implementation).
 * @return int 0 on success, 1 on failure.
 */
int		apply_redirs(t_redir *redirs, int fd, int dup_result, t_env *env);

// signals.c
/**
 * @brief Setup signal handlers for the shell.
 */
void	setup_signals(void);
/**
 * @brief Setup default signal handlers for child processes.
 */
void	setup_child_signals(void);

/**
 * @brief Execute a command with redirections in a child process.
 * 
 * @param cmd Command structure.
 * @param env Environment variables structures.
 * @return int 0 on success, 1 on failure.
 */
int		exec_redirs(t_cmd *cmd, t_env *env);

int		core_exec(t_cmd *cmd, t_env *env);

#endif