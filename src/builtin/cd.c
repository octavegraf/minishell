/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocgraf <ocgraf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 14:23:31 by ljudd             #+#    #+#             */
/*   Updated: 2025/08/06 16:56:37 by ocgraf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	mini_cd(char *prompt, t_env *env)
{
	char	path[1024];
	t_env	*pwd_env;

	if (search_env(env, "HOME") == NULL)
		ft_dprintf(2, "cd: HOME not set\n");
	if (chdir(prompt) == -1)
	{
		perror("cd");
		return (1);
	}
	if (!getcwd(path, 1024))
	{
		perror("cd");
		return (1);
	}
	pwd_env = search_env(env, "PWD");
	if (pwd_env)
		modify_env(pwd_env, NULL, path);
	return (0);
}

/* int	main(int argc, char **argv, char **envp)
{
	t_env	*env;
	t_env	*pwd_env;

	ft_printf("Mini CD Command\n");
	if (argc != 2)
	{
		ft_dprintf(2, "Usage: %s <path>\n", argv[0]);
		return (1);
	}
	env = get_env(envp);
	mini_cd(argv[1], env);
	pwd_env = search_env(env, "PWD");
	if (pwd_env)
		ft_printf("Current directory: %s\n", pwd_env->value);
	delete_all_env(env);
	return (0);
}
 */