/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocgraf <ocgraf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 19:33:31 by ljudd             #+#    #+#             */
/*   Updated: 2025/08/26 17:49:17 by ocgraf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/exec.h"

int	exec_builtin(t_cmd *cmd, t_env *env)
{
	if (!ft_strcmp(cmd->cmd_path, "cd"))
		return (mini_cd(cmd->args, env));
	else if (!ft_strcmp(cmd->cmd_path, "exit"))
		return (mini_exit(0));
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
	execve(cmd->cmd_path, cmd->args, env_to_array(env));
	perror("execve");
	return (1);
}

int	exec_in_child(t_cmd *cmd, t_env *env)
{
	int	pid;
	int	status;

	pid = fork();
	if (pid < 0)
		return (perror("fork"), -1);
	if (!pid)
		exec_function(cmd, env);
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
