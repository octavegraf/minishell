/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocgraf <ocgraf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 15:17:12 by ocgraf            #+#    #+#             */
/*   Updated: 2025/08/25 16:33:31 by ocgraf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/exec.h"

// Delete an environment variable
void	delete_env(t_env *to_delete, t_env *head)
{
	t_env	*prev;
	t_env	*next;

	while (head && head != to_delete)
	{
		prev = head;
		head = head->next;
	}
	next = head->next;
	if (prev)
		prev->next = next;
	free_env(to_delete);
}

void	delete_all_env(t_env *head)
{
	t_env	*next;

	next = NULL;
	while (head)
	{
		next = head->next;
		free_env(head);
		head = next;
	}
}

// Search for an environment variable by name
t_env	*search_env(t_env *head, const char *name)
{
	while (head && ft_strcmp(head->name, name) != 0)
	{
		head = head->next;
	}
	if (head)
		return (head);
	return (NULL);
}

t_env	*add_env(t_env *current_env, t_env *to_add)
{
	t_env	*next;

	next = current_env->next;
	current_env->next = to_add;
	to_add->next = next;
	return (to_add);
}

