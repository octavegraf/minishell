/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljudd <ljudd@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 14:04:31 by ocgraf            #+#    #+#             */
/*   Updated: 2025/10/06 16:22:21 by ljudd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/exec.h"

void	setup_child(t_cmd *cmd, int prev_pipefd, int *pipefd, t_data *data)
{
	setup_child_signals();
	if (prev_pipefd >= 0)
	{
		if (dup2(prev_pipefd, STDIN_FILENO) < 0)
			clean_exit(data, 1);
		close(prev_pipefd);
	}
	if (cmd->next)
	{
		if (dup2(pipefd[1], STDOUT_FILENO) < 0)
			clean_exit(data, 1);
		close(pipefd[1]);
		close(pipefd[0]);
	}
	if (apply_redirs(cmd->redirs))
		clean_exit(data, 1);
	close_heredocs(data->cmd);
	clean_exit(data, exec_function(cmd, data->env, data));
}

void	close_parent_pipes(t_cmd *cmd, int *prev_pipefd, int *pipefd)
{
	if (*prev_pipefd >= 0)
		close(*prev_pipefd);
	if (cmd->next)
	{
		close(pipefd[1]);
		*prev_pipefd = pipefd[0];
	}
}

int	wait_pipeline_processes(int *pid_array, int count)
{
	int	status;
	int	exit_code;
	int	i;

	i = 0;
	exit_code = 0;
	while (i < count)
	{
		waitpid(pid_array[i], &status, 0);
		if (WIFEXITED(status))
			exit_code = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			exit_code = 128 + WTERMSIG(status);
		i++;
	}
	return (exit_code);
}

static int	fork_pipeline_commands(t_cmd *cmd, t_data *data, int *pid_array,
		int *prev_pipefd)
{
	int		pipefd[2];
	pid_t	pid;
	int		count;

	count = 0;
	while (cmd)
	{
		if (cmd->next && pipe(pipefd) < 0)
			return (perror("pipe"), -1);
		pid = fork();
		if (pid < 0)
			return (perror("fork"), -1);
		if (pid == 0)
			setup_child(cmd, *prev_pipefd, pipefd, data);
		pid_array[count++] = pid;
		close_parent_pipes(cmd, prev_pipefd, pipefd);
		cmd = cmd->next;
	}
	return (count);
}

int	exec_pipeline(t_cmd *cmd, t_data *data, int count)
{
	int		prev_pipefd;
	int		pid_array[100];
	int		exit_code;

	if (count_cmd(cmd) > 100)
		return (ft_dprintf(2, "Too many commands in pipeline (>= 100)\n"));
	if (process_heredocs(cmd, data->env, data))
		return (1);
	prev_pipefd = -1;
	count = fork_pipeline_commands(cmd, data, pid_array, &prev_pipefd);
	if (count < 0)
		return (1);
	if (prev_pipefd >= 0)
		close(prev_pipefd);
	exit_code = wait_pipeline_processes(pid_array, count);
	close_heredocs(data->cmd);
	return (exit_code);
}
