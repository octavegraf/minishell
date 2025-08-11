/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocgraf <ocgraf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 14:26:32 by ljudd             #+#    #+#             */
/*   Updated: 2025/08/11 17:45:50 by ocgraf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env	*closest_env(t_env *head, const char *name)
{
	t_env	*current;
	t_env	*closest;
	int		cmp;

	current = head;
	closest = NULL;
	while (current)
	{
		cmp = ft_strcmp(current->name, name);
		if (cmp < 0)
		{
			if (!closest || ft_strcmp(current->name, closest->name) > 0)
				closest = current;
		}
		current = current->next;
	}
	return (closest);
}

t_env	*verify_env(t_env *env, char *prompt, char **name, char **value)
{
	int		i;
	int		equal;
	t_env	*current;

	current = NULL;
	equal = ft_strlen(prompt) - ft_strlen(ft_strchr(prompt, '='));
	if (!equal)
		return ;
	*name = ft_substr(prompt, 0, equal);
	if (!*name)
		return (ft_printf("export: Memory allocation failed\n"), 1);
	i = -1;
	while ((*name)[++i])
		if ((*name)[i] == ' ' || (*name)[i] == '\t' || (*name)[i] == '\n')
			return (ft_printf("export: Invalid identifier\n"), free(*name),
				NULL);
	if (ft_strchr(*name, ' ') || ft_strchr(*name, '\t')
		|| ft_strchr(*name, '\n'))
		return (ft_printf("export: Invalid identifier\n"), 1);
	*value = prompt + equal + 1;
}

int	mini_export(t_env *env, char *prompt)
{
	int		equal;
	char	*name;
	char	*value;
	t_env	*current;
	t_env	*new;

	if (!prompt || !*prompt)
		mini_env(env);
	else
	{
		verify_env(env, prompt, &name, &value);
		if (current)
			current->value = value;
		else
		{
			current = closest_env;
			new = create_env(name, value);
			if (!new)
				return (ft_printf("export: Memory allocation failed\n"), 1);
		}
	}
}
