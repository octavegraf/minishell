/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljudd <ljudd@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 17:45:17 by ocgraf            #+#    #+#             */
/*   Updated: 2025/10/06 16:20:03 by ljudd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/exec.h"

static int	should_apply_redir(t_redir *current)
{
	t_redir	*temp;

	if (current->type == REDIR_OUT || current->type == REDIR_APPEND)
		return (1);
	temp = current->next;
	while (temp)
	{
		if (temp->type == REDIR_IN || temp->type == REDIR_HEREDOC)
			return (0);
		temp = temp->next;
	}
	return (1);
}

int	apply_redirs(t_redir *redirs)
{
	int	fd;
	int	should_apply;

	while (redirs)
	{
		fd = open_redir_fd(redirs);
		if (fd < 0)
			return (perror("open"), 1);
		should_apply = should_apply_redir(redirs);
		if (should_apply)
		{
			if (apply_single_redir(redirs, fd))
				return (1);
		}
		close(fd);
		redirs = redirs->next;
	}
	return (0);
}

int	exec_redirs(t_cmd *cmd, t_env *env, t_data *data)
{
	pid_t	pid;
	int		status;
	int		exit_code;

	if (process_heredocs(cmd, env, data))
		return (1);
	pid = fork();
	if (pid < 0)
		return (perror("fork"), 1);
	if (pid == 0)
	{
		if (apply_redirs(cmd->redirs))
			clean_exit(data, 1);
		close_heredocs(cmd);
		clean_exit(data, exec_function(cmd, env, data));
	}
	waitpid(pid, &status, 0);
	close_heredocs(cmd);
	if (WIFEXITED(status))
		exit_code = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		exit_code = 128 + WTERMSIG(status);
	else
		exit_code = 1;
	return (exit_code);
}
