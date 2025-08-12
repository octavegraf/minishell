/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocgraf <ocgraf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 14:06:38 by ocgraf            #+#    #+#             */
/*   Updated: 2025/08/12 14:46:29 by ocgraf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "../libft/libft.h"
# include <stdio.h>

typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}	t_env;

/********************************** BUILT_IN **********************************/

// cd
int		mini_cd(char *path, t_env *env);

// echo
void	mini_echo(char **prompt);
int		disable_nl(char *prompt);

// env
int		mini_env(t_env *env);

// exit
int		mini_exit(int exit_code);

// export
int		mini_export(t_env *env, char **args);
int		mini_export2(t_env *env, char *name, char *value);
t_env	*insert_env(t_env *env, char *name, char *value);

// pwd
int		mini_pwd(void);

// unset
int		mini_unset(t_env *env, char **args);


// utils
char	*join_args(char **args);

/********************************** PAR_SING **********************************/

/************************************ EXEC ************************************/


// env
t_env	*get_env(char **envp);
t_env	*create_env(char *name, char *value);
t_env	*add_env_back(t_env *env, char *name, char *value);
void	free_env(t_env *env);
void	modify_env(t_env *env, char *name, char *value);

// env2
void	delete_env(t_env *to_delete, t_env *head);
void	delete_all_env(t_env *head);
t_env	*search_env(t_env *head, const char *name);
t_env	*add_env(t_env *current_env, t_env *to_add);


#endif