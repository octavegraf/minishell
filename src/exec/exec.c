/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocgraf <ocgraf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 19:33:31 by ljudd             #+#    #+#             */
/*   Updated: 2025/09/30 13:12:17 by ocgraf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/exec.h"

int	exec_builtin(t_cmd *cmd, t_env *env)
{
	if (!ft_strcmp(cmd->cmd_path, "cd"))
		return (mini_cd(cmd->args, env));
	else if (!ft_strcmp(cmd->cmd_path, "exit"))
		return (mini_exit(cmd->args));
	else if (!ft_strcmp(cmd->cmd_path, "export"))
		return (mini_export(env, cmd->args + 1));
	else if (!ft_strcmp(cmd->cmd_path, "unset"))
		return (mini_unset(env, cmd->args + 1));
	else if (!ft_strcmp(cmd->cmd_path, "echo"))
		return (mini_echo(cmd->args));
	else if (!ft_strcmp(cmd->cmd_path, "env"))
		return (mini_env(env));
	else if (!ft_strcmp(cmd->cmd_path, "pwd"))
		return (mini_pwd());
	else
		return (1);
	return (0);
}

int	exec_external(t_cmd *cmd, t_env *env)
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
			exit(1);
		}
	}
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(cmd->cmd_path, STDERR_FILENO);
	ft_putstr_fd(": command not found\n", STDERR_FILENO);
	double_free((void **)path);
	return (127);
}

int	exec_in_child(t_cmd *cmd, t_env *env)
{
	int	pid;
	int	status;

	pid = fork();
	if (pid < 0)
		return (perror("fork"), -1);
	if (!pid)
	{
		setup_child_signals();
		exit(exec_function(cmd, env));
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (1);
}

int	exec_function(t_cmd *cmd, t_env *env)
{
	if (is_builtin(cmd))
		return (exec_builtin(cmd, env));
	if (!is_builtin(cmd))
		return (exec_external(cmd, env));
	return (1);
}

int	exec_decide(t_cmd *cmd, t_env *env)
{
	if (is_builtin(cmd) == 2 || !is_builtin(cmd))
		return (exec_in_child(cmd, env));
	else
		return (exec_builtin(cmd, env));
	return (0);
}

/* int	main(int argc, char **argv, char **envp)
{
	t_cmd	*test_cmd;
	t_env	*env;
	char	**test_args;
	(void)argc, (void)argv;
	env = get_env(envp);
	test_cmd = malloc(sizeof(t_cmd));
	test_args = malloc(sizeof(char *) * 3);
	test_args[0] = "ls";
	test_args[1] = NULL;
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
} */