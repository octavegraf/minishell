/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocgraf <ocgraf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 14:23:31 by ljudd             #+#    #+#             */
/*   Updated: 2025/08/13 14:40:33 by ocgraf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	mini_cd(char *prompt, t_env *env)
{
	char	path[1024];
	t_env	*pwd_env;
	t_env	*old_pwd;
	char	*old_pwd_value;

	old_pwd = search_env(env, "OLDPWD");
	if (!old_pwd)
		return (ft_dprintf(2, "cd: OLDPWD not set\n"), 1);
	old_pwd_value = ft_strdup(old_pwd->value);
	if (!old_pwd_value)
		return (perror("malloc"), 1);
	if (!search_env(env, "HOME"))
		return (ft_dprintf(2, "cd: HOME not set\n"), 1);
	if (chdir(prompt) == -1)
		return (perror("cd"), 1);
	if (!getcwd(path, 1024))
		return (perror("cd"), 1);
	pwd_env = search_env(env, "PWD");
	if (pwd_env)
		modify_env(pwd_env, NULL, path);
	modify_env(old_pwd, NULL, old_pwd_value);
	free(old_pwd_value);
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
	pwd_env = search_env(env, "OLDPWD");
	if (pwd_env)
		ft_printf("Previous directory: %s\n", pwd_env->value);
	delete_all_env(env);
	return (0);
} */