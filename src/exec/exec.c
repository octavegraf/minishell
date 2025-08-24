/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocgraf <ocgraf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 19:33:31 by ljudd             #+#    #+#             */
/*   Updated: 2025/08/24 17:21:36 by ocgraf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/exec.h"

int	exec_function(t_cmd *cmd, t_env *env)
{
	char	**path;
	int		i;

	path = ft_split(search_env(env, "PATH")->value, ':');
	if (!path)
		return (1);
	i = -1;
	path = path_to_array(path, cmd);
	if (!path)
		return (1);
	while (path[++i])
	{
		if (access(path[i], X_OK) == 0)
		{
			execve(path[i], cmd->args, env_to_array(env));
			perror("execve");
			return (1);
		}
	}
	free(path);
	return (1);
}

int	exec_child(t_cmd *cmd, t_env *env)
{
	if (is_builtin(cmd) == 1)
		return (exec_builtin(cmd, env));
	else if (is_builtin(cmd) == 2)
	{
		if (fork() == 0)
			return (exec_builtin(cmd, env));
	}
	else
	{
		if (fork() == 0)
			return (exec_function(cmd, env));
	}
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_cmd	*test_cmd;
	t_env	*env;
	char	**test_args;
	(void)argc, (void)argv;
	env = get_env(envp);
	test_cmd = malloc(sizeof(t_cmd));
	test_args = malloc(sizeof(char *) * 3);
	test_args[0] = "ls";
	test_args[1] = "-la";
	test_args[2] = NULL;
	test_cmd->args = test_args;
	test_cmd->cmd_path = NULL;
	test_cmd->redirs = NULL;
	test_cmd->next = NULL;
	if (is_builtin(test_cmd))
		printf("ls is builtin\n");
	else
		printf("ls is not builtin\n");
	test_cmd->cmd_path = "cd";
	test_cmd->args[0] = "cd";
	if (is_builtin(test_cmd))
		printf("cd is builtin\n");
	else
		printf("cd is not builtin\n");
	test_cmd->cmd_path = "ls";
	test_cmd->args[0] = "ls";
	exec_function(test_cmd, env);
	free(test_args);
	free(test_cmd);
	free_env(env);
	return (0);
}

