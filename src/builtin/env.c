/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocgraf <ocgraf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 14:21:51 by ljudd             #+#    #+#             */
/*   Updated: 2025/08/25 16:30:47 by ocgraf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/builtin.h"

int	mini_env(t_env *env)
{
	while (env)
	{
		ft_printf("%s=%s\n", env->name, env->value);
		env = env->next;
	}
	return (0);
}
/* int main(int argc, char **argv, char **envp)
{
	t_env *env = NULL;
	env = get_env(envp);
	(void)argc;
	(void)argv;
	mini_env(env);
	return (0);
}
 */