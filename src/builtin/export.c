/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocgraf <ocgraf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 14:26:32 by ljudd             #+#    #+#             */
/*   Updated: 2025/10/02 15:28:51 by ocgraf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/builtin.h"

int	is_valid_identifier(char *name)
{
	int	i;

	if (!name || !*name)
		return (0);
	if (!ft_isalpha(name[0]) && name[0] != '_')
		return (0);
	i = 0;
	while (name[++i])
	{
		if (!ft_isalnum(name[i]) && name[i] != '_')
			return (0);
	}
	return (1);
}

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

	if (!is_valid_identifier(name))
	{
		ft_dprintf(2, "export: `%s': not a valid identifier\n", name);
		free(name);
		if (value)
			free(value);
		return (1);
	}
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
	int		has_error;

	if (!args || !**args)
		return (mini_env(env));
	i = -1;
	has_error = 0;
	while (args[++i])
	{
		equal = ft_strchr(args[i], '=');
		if (!equal)
		{
			if (!is_valid_identifier(args[i]))
			{
				ft_dprintf(2, "export: `%s': not a valid identifier\n", args[i]);
				has_error = 1;
			}
			continue ;
		}
		if (ft_strchr(equal + 1, '='))
			continue ;
		name = ft_substr(args[i], 0, equal - args[i]);
		if (!name)
			return (ft_dprintf(2, "export: Memory allocation failed\n"), 1);
		if (mini_export2(env, name, ft_substr(equal + 1, 0,
					ft_strlen(equal + 1))))
			has_error = 1;
	}
	return (has_error);
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