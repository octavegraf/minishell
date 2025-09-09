/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocgraf <ocgraf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 14:04:31 by ocgraf            #+#    #+#             */
/*   Updated: 2025/09/09 15:50:42 by ocgraf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/exec.h"

int	exec_pipeline(t_cmd *cmd, t_env *env)
{
	int		pipefd[2];
	pid_t	pid;
	int		count;

	count = 0;
	while (cmd)
	{
		pipe(pipefd);
		pid = fork();
		if (pid < 0)
			return (perror("fork"), 1);
		if (pid == 0)
		{
			if (count)
				if (dup2(pipefd[0], STDIN_FILENO) < 0)
					return (perror("dup2"), 1);
			if (dup2(pipefd[1], STDOUT_FILENO) < 0)
				return (perror("dup2"), 1);
			if (apply_redirs(cmd->redirs, 0, 0))
				return (-1);
			if (exec_function(cmd, env))
				return (-1);
		}
		close(pipefd[1]);
		cmd = cmd->next;
		count++;
		waitpid(pid, NULL, 0);
	}
	return (pipefd[0]);
}
