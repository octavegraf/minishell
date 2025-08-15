/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocgraf <ocgraf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 14:27:03 by ljudd             #+#    #+#             */
/*   Updated: 2025/08/15 12:47:57 by ocgraf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	mini_unset(t_env *env, char **args)
{
	int		i;
	t_env	*to_delete;

	if (!args || !*args)
		return (ft_dprintf(2, "unset: not enough arguments\n"), 1);
	i = -1;
	while (args[++i])
	{
		to_delete = search_env(env, args[i]);
		if (to_delete)
			delete_env(to_delete, env);
	}
	return (0);
}

/* int main(int argc, char **argv, char **envp)
{
	t_env	*env;

	env = get_env(envp);
	(void)argv, (void)argc;
	mini_unset(env, NULL);
	mini_env(env);
	return (0);
} */