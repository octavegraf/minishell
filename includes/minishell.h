/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljudd <ljudd@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 14:06:38 by ocgraf            #+#    #+#             */
/*   Updated: 2025/08/11 15:32:49 by ljudd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "../libft/libft.h"
# include <stdio.h>
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>

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

/* t_data :
	core structure handling all the elements used in the program
	env : see struct above
	exit_code : last exit code returned by a command
	inputs : inputs read by readline
*/
typedef struct s_data
{
	t_env	env;
	int		exit_code;
	char	*inputs;
}	t_data;

/********************************** BUILTIN ***********************************/

/*	cd	*/

int		mini_cd(char *path, t_env *env);

/********************************** PARSING ***********************************/


/************************************ EXEC ************************************/

/*	env	*/

t_env	*get_env(char **envp);
t_env	*create_env(char *name, char *value);
t_env	*add_env(t_env *env, char *name, char *value);
void	free_env(t_env *env);
void	modify_env(t_env *env, char *name, char *value);

/*	env2	*/

void	delete_env(t_env *to_delete, t_env *head);
void	delete_all_env(t_env *head);
t_env	*search_env(t_env *head, const char *name);

#endif