/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljudd <ljudd@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 14:06:38 by ocgraf            #+#    #+#             */
/*   Updated: 2025/08/24 11:50:36 by ljudd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "libft.h"
# include <stdio.h>
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>

/******************************** STRUCTURES **********************************/

/* t_env :
	structure to handle the environnement variables
	Defined as a chained dictionnary
*/
typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}	t_env;

/* t_node_type :
	Types of nodes :
	- TREE_CMD command
	- TREE_PIPE |
	- TREE_REDIR (< > >> <<)
*/
typedef enum e_node_type
{
	TREE_CMD,
	TREE_PIPE,
	TREE_REDIR,
}	t_node_type;

/* t_redir_type :
	Types of redirection :
	- REDIR_IN <
	- REDIR_OUT >
	- REDIR_APPEND >>
	- REDIR_HEREDOC <<
*/
typedef enum e_redir_type
{
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	REDIR_HEREDOC,
}	t_redir_type;

/* t_token :
	structure to handle the pretokenization to tokenization phase :
	- type : preidentified type of the token
	- inputs : text
	- quoted : if infos are quoted or not, and which type of quote (single/doub)
	- target : only used in tokenization phase, info of the redirection
	- next and past : chained list in two ways, to easily get the target for
		redirection
*/
typedef struct s_token
{
	t_node_type		type;
	t_redir_type	redir_type;
	char			*inputs;
	char			quoted;
	char			*target;
	struct s_token	*next;
	struct s_token	*past;
}	t_token;

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

/* t_redir :
	list of all the redirections to do before exectuing the command
	- type : type of the redirection
	- target : target of the redirection (what it does depends of redir type)
	- heredoc_fd : fd for the heredoc
	- next : next elem
*/
typedef struct s_redir
{
	t_redir_type	type;
	char			*target;
	int				heredoc_fd;
	struct s_redir	*next;
}	t_redir;

/* t_cmd :
	list of all the cmds to execute :
	- args : list of arguments (cf execve)
	- cmd_path : path of the command (cf execve)
	- redirs : cf redir structure, list of all the redirs to do before exec
	- next : next elem
*/
typedef struct s_cmd
{
	char			**args;
	char			*cmd_path;
	t_redir			*redirs;
	struct s_cmd	*next;
}	t_cmd;

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
	t_env	env;
	int		exit_code;
	char	*inputs;
	bool	error_parse;
	t_token	*token;
}	t_data;

/******************************** TEMPORARY **********************************/

void	core_parsing(t_data *data);

void	core_exec(t_data *data);

void	clean_exit(int exit_code);
char	*ft_strcpy_ij(char *src, int i, int j);

/********************************** BUILT_IN **********************************/

/* cd */

int		mini_cd(char *path, t_env *env);

/* echo */

void	mini_echo(char **prompt);
int		disable_nl(char *prompt);

/* env */

int		mini_env(t_env *env);

/* exit */

int		mini_exit(int exit_code);

/* export */

int		mini_export(t_env *env, char **args);
int		mini_export2(t_env *env, char *name, char *value);
t_env	*insert_env(t_env *env, char *name, char *value);

/* pwd */

int		mini_pwd(void);

/* unset */

int		mini_unset(t_env *env, char **args);

/* utils */

char	*join_args(char **args);

/*********************************** PARSING **********************************/

void	pretoken_rec(t_data *data, int *i, int *j, t_token **token);

/************************************ EXEC ************************************/

/* env */

t_env	*get_env(char **envp);
t_env	*create_env(char *name, char *value);
t_env	*add_env_back(t_env *env, char *name, char *value);
void	free_env(t_env *env);
void	modify_env(t_env *env, char *name, char *value);

/* env2 */

void	delete_env(t_env *to_delete, t_env *head);
void	delete_all_env(t_env *head);
t_env	*search_env(t_env *head, const char *name);
t_env	*add_env(t_env *current_env, t_env *to_add);

#endif