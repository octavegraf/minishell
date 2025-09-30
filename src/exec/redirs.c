/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocgraf <ocgraf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 17:45:17 by ocgraf            #+#    #+#             */
/*   Updated: 2025/09/30 11:54:45 by ocgraf           ###   ########.fr       */
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
		if (!line || is_heredoc_interrupted())
		{
			if (line)
				free(line);
			break ;
		}
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

int	create_heredoc(const char *end, t_env *env)
{
	int		pipe_fd[2];
	pid_t	pid;

	if (pipe(pipe_fd))
		return (perror("pipe"), -1);
	pid = fork();
	if (pid < 0)
		return (perror("fork"), -1);
	if (pid == 0)
	{
		close(pipe_fd[0]);
		heredoc_child_process(pipe_fd[1], end, env);
		close(pipe_fd[1]);
		if (is_heredoc_interrupted())
			exit(1);
		exit(0);
	}
	close(pipe_fd[1]);
	waitpid(pid, NULL, 0);
	return (pipe_fd[0]);
}

int	apply_redirs(t_redir *redirs, int fd, int dup_result, t_env *env)
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
			fd = create_heredoc(redirs->target, env);
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
		if (apply_redirs(cmd->redirs, 0, 0, env))
			exit(1);
		exec_function(cmd, env);
		exit(1);
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (1);
}

// int	main(int argc, char **argv, char **envp)
// {
// 	t_cmd	cmd;
// 	t_redir redir;
// 	char	*args[] = {"cat", "-e", NULL};
// 	t_env	*env = NULL;
// 	redir.type = REDIR_HEREDOC;
// 	redir.target = "EOF";
// 	redir.heredoc_fd = -1;
// 	redir.next = NULL;
// 	cmd.args = args;
// 	cmd.cmd_path = "cat";
// 	cmd.redirs = &redir;
// 	cmd.next = NULL;
// 	(void)argc, (void)argv;
// 	env = get_env(envp);
// 	int ret = exec_redirs(&cmd, env);
// 	printf("%d\n", ret);
// 	delete_all_env(env);
// 	return (0);
// }

// int	main(int ac, char **av, char **envp)
// {
// 	(void)ac;
// 	(void)av;

// 	t_env	*env = get_env(envp);
// 	while (1)
// 	{
// 		char	*input = readline("minishell$ ");
// 		if (!input)
// 			break ;
// 		if (ft_strlen(input) > 0)
// 			add_history(input);
// 		t_data	data;
// 		data.env = env;
// 		data.exit_code = 0;
// 		data.inputs = input;
// 		data.error_parse = false;
// 		data.token = NULL;
// 		data.cmd = malloc(sizeof(t_cmd));
// 		ft_bzero(data.cmd, sizeof(t_cmd));
// 		data.cmd->redirs = malloc(sizeof(t_redir));
// 		ft_bzero(data.cmd->redirs, sizeof(t_redir));
// 		// ex: cat -e < EOF
// 		char	**redir_input = ft_split(input, '<');
// 		// redir_input[0] = "cat -e " ; redir_input[1] = " EOF"
// 		data.cmd->redirs->target = redir_input[1];
// 		// target = " EOF"
// 		data.cmd->redirs->type = REDIR_HEREDOC;
// 		// redir_input[0] = "cat -e "
// 		data.cmd->args = ft_split(redir_input[0], ' ');
// 		// args = {"cat", "-e", NULL}
// 		data.cmd->cmd_path = data.cmd->args[0];
// 		// cmd_path = "cat"
// 		core_exec(data.cmd, data.env);
// 		free(input);
// 		double_free((void **)data.cmd);
// 	}
// }