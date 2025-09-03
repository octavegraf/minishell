/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocgraf <ocgraf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 17:45:17 by ocgraf            #+#    #+#             */
/*   Updated: 2025/09/03 09:57:11 by ocgraf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/exec.h"

int	open_redir_out(t_redir *redir, int append)
{
	if (!redir || !redir->target)
		return (-1);
	if (append)
		return (open(redir->target, O_WRONLY | O_CREAT | O_APPEND, 0644));
	else
		return (open(redir->target, O_WRONLY | O_CREAT | O_TRUNC, 0644));
}

int	open_redir_in(t_redir *redir)
{
	if (!redir || !redir->target)
		return (-1);
	return (open(redir->target, O_RDONLY));
}

int	create_heredoc(const char *end)
{
	int		pipe_fd[2];
	pid_t	pid;
	char	*line;

	if (pipe(pipe_fd))
		return (perror("pipe"), -1);
	pid = fork();
	if (pid < 0)
		return (perror("fork"), -1);
	if (pid == 0)
	{
		close(pipe_fd[0]);
		while (1)
		{
			line = readline("> ");
			if (!line || !ft_strcmp(line, end))
				return (free(line), close(pipe_fd[1]), exit(0), 1);
			write(pipe_fd[1], line, ft_strlen(line));
			write(pipe_fd[1], "\n", 1);
			free(line);
		}
	}
	close(pipe_fd[1]);
	waitpid(pid, NULL, 0);
	return (pipe_fd[0]);
}

int	apply_redirs(t_redir *redirs, int fd, int dup_result)
{
	while (redirs)
	{
		if (redirs->type == REDIR_OUT)
			fd = open_redir_out(redirs, 0);
		else if (redirs->type == REDIR_APPEND)
			fd = open_redir_out(redirs, 1);
		else if (redirs->type == REDIR_IN)
			fd = open_redir_in(redirs);
		else if (redirs->type == REDIR_HEREDOC)
		{
			fd = create_heredoc(redirs->target);
		}
		if (fd < 0)
			return (perror("open"), 1);
		if (redirs->type == REDIR_OUT || redirs->type == REDIR_APPEND)
			dup_result = dup2(fd, STDOUT_FILENO);
		else
			dup_result = dup2(fd, STDIN_FILENO);
		close(fd);
		if (dup_result < 0)
			return (perror("dup2"), 1);
		redirs = redirs->next;
	}
	return (0);
}

int	exec_redirs(t_cmd *cmd, t_env *env)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid < 0)
		return (perror("fork"), 1);
	if (pid == 0)
	{
		if (apply_redirs(cmd->redirs, 0, 0))
			exit(1);
		exec_function(cmd, env);
		exit(1);
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (1);
}

/* int	main(int argc, char **argv, char **envp)
{
	t_cmd	cmd;
	t_redir redir;
	char	*args[] = {"ls", "-l", NULL};
	t_env	*env = NULL;
	redir.type = REDIR_OUT;
	redir.target = "out.txt";
	redir.heredoc_fd = -1;
	redir.next = NULL;
	cmd.args = args;
	cmd.cmd_path = "ls";
	cmd.redirs = &redir;
	cmd.next = NULL;
	(void)argc, (void)argv;
	env = get_env(envp);
	int ret = exec_redirs(&cmd, env);
	printf("%d\n", ret);
	delete_all_env(env);
	return (0);
} */