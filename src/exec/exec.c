/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocgraf <ocgraf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 19:33:31 by ljudd             #+#    #+#             */
/*   Updated: 2025/10/03 12:28:43 by ocgraf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/exec.h"

int	exec_builtin(t_cmd *cmd, t_env *env)
{
	if (!cmd->cmd_path)
		return (1);
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

int	exec_direct_path(t_cmd *cmd, t_env *env)
{
	struct stat	statbuf;

	if (stat(cmd->cmd_path, &statbuf) == 0 && S_ISDIR(statbuf.st_mode))
		return (ft_dprintf(2, "minishell: %s: is a folder\n",
				cmd->cmd_path), 126);
	if (access(cmd->cmd_path, F_OK) == 0 && access(cmd->cmd_path, X_OK) != 0)
		return (ft_dprintf(2, "minishell: %s permission denied\n",
				cmd->cmd_path), 126);
	if (access(cmd->cmd_path, X_OK) == 0)
	{
		execve(cmd->cmd_path, cmd->args, env_to_array(env));
		return (perror("execve"), 126);
	}
	return (ft_dprintf(2, "minishell: %s: no such file or directory\n",
			cmd->cmd_path), 127);
}

int	exec_from_path(t_cmd *cmd, t_env *env, char **path)
{
	int	i;

	i = -1;
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

int	exec_external(t_cmd *cmd, t_env *env)
{
	char		**path;
	t_env		*path_env;

	if (!cmd->cmd_path || !cmd->cmd_path[0])
		return (0);
	if (ft_strchr(cmd->cmd_path, '/'))
		return (exec_direct_path(cmd, env));
	path_env = search_env(env, "PATH");
	if (!path_env)
		return (ft_dprintf(2, "minishell: %s: command not found\n",
				cmd->cmd_path), 127);
	path = ft_split(path_env->value, ':');
	if (!path)
		return (1);
	path = path_to_array(path, cmd);
	if (!path)
		return (1);
	return (exec_from_path(cmd, env, path));
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