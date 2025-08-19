/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocgraf <ocgraf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 14:06:38 by ocgraf            #+#    #+#             */
/*   Updated: 2025/08/19 16:15:47 by ocgraf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "libft.h"
# include <stdio.h>
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>

/********************************** E_NUMS ************************************/
typedef enum e_redir_type
{
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	REDIR_HEREDOC,
}	t_redir_type;

typedef enum e_node_type
{
	TREE_CMD,
	TREE_PIPE,
	TREE_REDIR,
}	t_node_type;

/******************************** STRUCTURES **********************************/
typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}	t_env;

/* t_token :
	structure to handle the pretokenization to tokenization phase :
	- type : preidentified type of the token
	- inputs : text
	- quoted : if infos are quoted or not, and which type of quote (single/doub)
	- target : only used in tokenization phase, info of the redirection
*/
typedef struct s_token
{
	t_node_type		type;
	char			*inputs;
	char			quoted;
	char			*target;
	struct s_token	*next;
	struct s_token	*past;
}	t_token;

/* t_data :
	core structure handling all the elements used in the program
	- env : see struct above
	- exit_code : last exit code returned by a command
	- inputs : inputs read by readline
	- error_parse : boolean that indicates that an error happened during parsing
	- token : token of the inputs through the tokenization phase
*/
typedef struct s_data
{
	t_env	*env;
	int		exit_code;
	char	*inputs;
	bool	error_parse;
	t_token	*token;
}	t_data;

/* t_tree :
	tree of the different elements
	- type : indicates the type of the node
	- tree_cmd : cmds with the *inputs
	- tree_pipe : pipe node with left node (first to execute) and right (2nd)
	- tree_redir : type of redir (cf enum) + the target of the redir and the
		node post redirection
*/
typedef struct s_tree
{
	t_node_type	type;
	union u_tree
	{
		struct s_tree_cmd
		{
			char		*inputs;
		} cmd;
		struct s_tree_pipe
		{
			struct s_tree	*left;
			struct s_tree	*right;
		} pipe;
		struct s_tree_redir
		{
			t_redir_type	type;
			char			*target;
			struct s_tree	*child;
		} redir;
	} tree;
}	t_tree;

typedef struct s_redir
{
	t_redir_type		type;
	char				*target;
	int					heredoc_fd;
	struct s_redir		*next;
}	t_redir;

typedef struct s_cmd
{
	char			**args;
	char			*cmd_path;
	t_redir			*redirs;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_garb
{
	void			*ptr;
	struct t_garb	*next;
}	t_garb;

/********************************** BUILT_IN **********************************/
// cd.c
int		mini_cd(char **args, t_env *env);

// echo.c
void	mini_echo(char **prompt);
int		disable_nl(char *prompt);

// env.c
int		mini_env(t_env *env);

// exit.c
int		mini_exit(int exit_code);

// export.c
int		mini_export(t_env *env, char **args);
int		mini_export2(t_env *env, char *name, char *value);
t_env	*insert_env(t_env *env, char *name, char *value);

// pwd.c
int		mini_pwd(void);

// unset.c
int		mini_unset(t_env *env, char **args);

/********************************** PAR_SING **********************************/

/************************************ EXEC ************************************/
// args.c
char	*join_args(char **args);
int		args_count(char **args);

// exec.c
bool	is_builtin(t_cmd *cmd);
int		exec_function(t_cmd *cmd, t_env *env);

// env_to_array.c
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

// env2.c
void	delete_env(t_env *to_delete, t_env *head);
void	delete_all_env(t_env *head);
t_env	*search_env(t_env *head, const char *name);
t_env	*add_env(t_env *current_env, t_env *to_add);

#endif