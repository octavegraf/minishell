/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljudd <ljudd@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 11:30:23 by ocgraf            #+#    #+#             */
/*   Updated: 2025/10/05 13:48:30 by ljudd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include <stdbool.h>
# include <stddef.h>

/**
 * @brief Enum that handle the different types of redirections.
 * @param REDIR_IN <
 * @param REDIR_OUT >
 * @param REDIR_APPEND >>
 * @param REDIR_HEREDOC <<
*/
typedef enum e_redir_type
{
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	REDIR_HEREDOC,
}	t_redir_type;

/**
 * @brief Enum that handle the different types of nodes in the syntax tree.
 * @param TREE_CMD command
 * @param TREE_PIPE |
 * @param TREE_REDIR (< > >> <<)
*/
typedef enum e_node_type
{
	TREE_CMD,
	TREE_PIPE,
	TREE_REDIR,
	TREE_ND,
}	t_node_type;

/**
 * @brief Chained list that handle the environment variables.
 * @param name Name of the environment variable.
 * @param value Value of the environment variable.
 * @param next Next element.
*/
typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}	t_env;

/**
 * @brief Structure to handle the pretokenization to tokenization phase.
 * @param type Preidentified type of the token.
 * @param inputs Text.
 * @param quoted If infos are quoted or not, the type of quote (single/double).
 * @param target Only used in tokenization phase, info of the redirection.
 * @param space_before True if a space precedes this token.
 * @param next Next element.
 * @param past Previous element.
*/
typedef struct s_token
{
	t_node_type		type;
	t_redir_type	redir_type;
	char			*inputs;
	char			quoted;
	char			*target;
	bool			space_before;
	struct s_token	*next;
	struct s_token	*past;
}	t_token;

/**
 * @brief List of all the redirections to do before executing the command.
 * @param type Type of the redirection.
 * @param target Target of the redirection (what it does depends of redir type).
 * @param heredoc_fd File descriptor for the heredoc.
*/
typedef struct s_redir
{
	t_redir_type		type;
	char				*target;
	int					heredoc_fd;
	struct s_redir		*next;
}	t_redir;

/**
 * @brief Command structure containing all the information needed to execute
 * a command.
 * @param args Array of arguments for the command.
 * @param cmd_path Path to the command executable.
 * @param redirs List of redirections associated with the command.
 * @param next Next element.
*/
typedef struct s_cmd
{
	char			**args;
	char			*cmd_path;
	t_redir			*redirs;
	struct s_cmd	*next;
}	t_cmd;

/**
 * @brief Core structure handling all the elements used in the program.
 * @param env Env structure.
 * @param exit_code Last exit code returned by a command.
 * @param inputs Inputs read by readline.
 * @param error_parse Indicates that an error happened during parsing.
 * @param token Token of the inputs through the tokenization phase.
*/
typedef struct s_data
{
	t_env	*env;
	int		exit_code;
	char	*inputs;
	bool	error_parse;

	t_token	*token;
	t_cmd	*cmd;
}	t_data;

#endif