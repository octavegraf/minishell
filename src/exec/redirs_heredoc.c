/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocgraf <ocgraf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 11:25:46 by ocgraf            #+#    #+#             */
/*   Updated: 2025/10/06 17:58:28 by ocgraf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/exec.h"

void	heredoc_child_process(int pipe_fd, const char *end, t_env *env)
{
	char	*line;
	char	*expanded_line;
	t_data	temp_data;

	temp_data.env = env;
	setup_heredoc_signals();
	while (1)
	{
		line = readline("> ");
		if (!line || get_heredoc_interrupted())
			break ;
		if (!ft_strcmp(line, end))
		{
			free(line);
			break ;
		}
		expanded_line = expand_inputs(line, &temp_data);
		write(pipe_fd, expanded_line, ft_strlen(expanded_line));
		write(pipe_fd, "\n", 1);
		free(line);
		if (expanded_line != line)
			free(expanded_line);
	}
}

int	create_heredoc(const char *end, t_env *env, t_data *data)
{
	int		pipe_fd[2];
	pid_t	pid;
	int		status;

	if (pipe(pipe_fd))
		return (perror("pipe"), -1);
	pid = fork();
	if (pid < 0)
		return (perror("fork"), -1);
	if (pid == 0)
	{
		close_heredocs(data->cmd);
		close(pipe_fd[0]);
		heredoc_child_process(pipe_fd[1], end, env);
		close(pipe_fd[1]);
		if (get_heredoc_interrupted())
			clean_exit(data, 1);
		clean_exit(data, 0);
	}
	close(pipe_fd[1]);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status) && WEXITSTATUS(status) == 1)
		return (close(pipe_fd[0]), -2);
	return (pipe_fd[0]);
}

int	process_heredocs(t_cmd *cmd, t_env *env, t_data *data)
{
	t_cmd	*current_cmd;
	t_redir	*current_redir;

	current_cmd = cmd;
	while (current_cmd)
	{
		current_redir = current_cmd->redirs;
		while (current_redir)
		{
			if (current_redir->type == REDIR_HEREDOC)
			{
				current_redir->heredoc_fd = create_heredoc(
						current_redir->target, env, data);
				if (current_redir->heredoc_fd == -2)
					return (1);
				if (current_redir->heredoc_fd < 0)
					return (perror("heredoc"), 1);
			}
			current_redir = current_redir->next;
		}
		current_cmd = current_cmd->next;
	}
	return (0);
}

void	close_heredocs(t_cmd *cmd)
{
	t_cmd	*current_cmd;
	t_redir	*current_redir;

	current_cmd = cmd;
	while (current_cmd)
	{
		current_redir = current_cmd->redirs;
		while (current_redir)
		{
			if (current_redir->type == REDIR_HEREDOC
				&& current_redir->heredoc_fd >= 0)
				close(current_redir->heredoc_fd);
			current_redir = current_redir->next;
		}
		current_cmd = current_cmd->next;
	}
}

void	close_unused_heredocs(t_cmd *all_cmds, t_cmd *current_cmd)
{
	t_cmd	*cmd_iter;
	t_redir	*redir_iter;

	cmd_iter = all_cmds;
	while (cmd_iter)
	{
		if (cmd_iter != current_cmd)
		{
			redir_iter = cmd_iter->redirs;
			while (redir_iter)
			{
				if (redir_iter->type == REDIR_HEREDOC
					&& redir_iter->heredoc_fd >= 0)
					close(redir_iter->heredoc_fd);
				redir_iter = redir_iter->next;
			}
		}
		cmd_iter = cmd_iter->next;
	}
}
