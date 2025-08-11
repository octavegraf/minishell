/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocgraf <ocgraf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 14:06:38 by ocgraf            #+#    #+#             */
/*   Updated: 2025/08/11 15:35:08 by ocgraf           ###   ########.fr       */
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