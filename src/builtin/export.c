/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljudd <ljudd@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 14:26:32 by ljudd             #+#    #+#             */
/*   Updated: 2025/08/13 14:52:38 by ljudd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*insert_env(t_env *env, char *name, char *value)
{
	t_env	*new_env;
	t_env	*current;
	t_env	*prev;

	new_env = create_env(name, value);
	if (!new_env)
		return (NULL);
	current = env;
	prev = NULL;
	while (current && ft_strcmp(name, current->name) > 0)
	{
		prev = current;
		current = current->next;
	}
	new_env->next = current;
	if (prev)
		prev->next = new_env;
	return (new_env);
}

int	mini_export2(t_env *env, char *name, char *value)
{
	t_env	*current;

	if (!env)
	{
		if (!create_env(name, value))
			return (ft_dprintf(2, "export: Memory allocation failed\n"), 1);
	}
	current = search_env(env, name);
	if (current)
		modify_env(current, name, value);
	else
		if (!insert_env(env, name, value))
			return (ft_dprintf(2, "export: Memory allocation failed\n"), 1);
	return (0);
}

int	mini_export(t_env *env, char **args)
{
	char	*equal;
	char	*name;
	int		i;

	if (!args || !**args)
		return (mini_env(env));
	i = -1;
	while (args[++i])
	{
		if (!ft_strchr(args[i], '=') || ft_strchr(args[i], ' ')
			|| ft_strchr(args[i], '\t') || ft_strchr(args[i], '\n')
			|| ft_strchr(args[i], '\r') || ft_strchr(args[i], '\v')
			|| ft_strchr(args[i], '\f'))
			continue ;
		equal = ft_strchr(args[i], '=');
		if (ft_strchr(equal + 1, '='))
			continue ;
		name = ft_substr(args[i], 0, equal - args[i]);
		if (!name)
			return (ft_dprintf(2, "export: Memory allocation failed\n"), 1);
		if (mini_export2(env, name, ft_substr(equal + 1, 0,
					ft_strlen(equal + 1))))
			return (1);
	}
	return (0);
}

/* int main(int argc, char **argv, char **envp)
{
	t_env	*env;

	(void)argc;
	(void)argv;
	env = get_env(envp);
	mini_export(env, NULL);
	return (0);
} */