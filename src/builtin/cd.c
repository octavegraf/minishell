/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocgraf <ocgraf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 14:23:31 by ljudd             #+#    #+#             */
/*   Updated: 2025/08/24 16:22:26 by ocgraf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/builtin.h"

int	mini_cd(char **args, t_env *env)
{
	char	path[1024];
	t_env	*pwd_env;
	t_env	*old_pwd;
	t_env	*home_env;

	if (args_count(args) > 1)
		return (ft_dprintf(2, "cd: too many arguments\n"), 1);
	pwd_env = search_env(env, "PWD");
	if (!pwd_env)
		return (ft_dprintf(2, "cd: PWD not set\n"), -1);
	old_pwd = search_env(env, "OLDPWD");
	if (!old_pwd)
		return (ft_dprintf(2, "cd: OLDPWD not set\n"), -1);
	home_env = search_env(env, "HOME");
	if (!home_env)
		return (ft_dprintf(2, "cd: HOME not set\n"), -1);
	if (args_count(args) == 0 || !ft_strcmp(args[0], "~"))
		if (chdir(home_env->value))
			return (perror("chdir"), 1);
	if (!getcwd(path, 1024))
		return (perror("getcwd"), 1);
	if (modify_env(old_pwd, NULL, pwd_env->value)
		|| modify_env(pwd_env, NULL, path))
		return (perror("malloc"), -1);
	return (0);
}

/* int	main(int argc, char **argv, char **envp)
{
	t_env	*env;
	t_env	*pwd_env;

	(void)argc;
	env = get_env(envp);
	mini_cd(argv + 1, env);
	pwd_env = search_env(env, "PWD");
	if (pwd_env)
		ft_printf("Current directory: %s\n", pwd_env->value);
	pwd_env = search_env(env, "OLDPWD");
	if (pwd_env)
		ft_printf("Previous directory: %s\n", pwd_env->value);
	delete_all_env(env);
	return (0);
} */