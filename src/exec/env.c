/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocgraf <ocgraf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 14:43:28 by ocgraf            #+#    #+#             */
/*   Updated: 2025/08/06 16:52:36 by ocgraf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env	*get_env(char **envp)
{
	t_env	*env;
	int		i;
	int		sep;
	char	*sub;

	env = NULL;
	i = -1;
	while (envp[++i])
	{
		sep = ft_strlen(envp[i]) - ft_strlen(ft_strchr(envp[i], '='));
		sub = ft_substr(envp[i], 0, sep);
		if (!sub)
		{
			delete_all_env(env);
			return (NULL);
		}
		env = add_env(env, sub, ft_strchr(envp[i], '=') + 1);
		free(sub);
	}
	return (env);
}

t_env	*create_env(char *name, char *value)
{
	t_env	*new_env;

	new_env = malloc(sizeof(t_env));
	if (!new_env)
		return (NULL);
	new_env->name = ft_strdup(name);
	new_env->value = ft_strdup(value);
	new_env->next = NULL;
	return (new_env);
}

t_env	*add_env(t_env *env, char *name, char *value)
{
	t_env	*new_env;
	t_env	*current;

	new_env = create_env(name, value);
	if (!new_env)
		return (NULL);
	if (!env)
		return (new_env);
	current = env;
	while (current->next)
		current = current->next;
	current->next = new_env;
	return (env);
}

void	modify_env(t_env *env, char *name, char *value)
{
	if (!env)
		return ;
	if (name)
	{
		free(env->name);
		env->name = ft_strdup(name);
	}
	if (value)
	{
		free(env->value);
		env->value = ft_strdup(value);
	}
}

void	free_env(t_env *env)
{
	if (!env)
		return ;
	free(env->name);
	free(env->value);
	free(env);
}

/* Getting environments variables */