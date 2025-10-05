/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljudd <ljudd@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 11:25:46 by ocgraf            #+#    #+#             */
/*   Updated: 2025/10/05 17:52:16 by ljudd            ###   ########.fr       */
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
		if (get_heredoc_interrupted())
			clean_exit(data, 1);
		clean_exit(data, 0);
	}
	close(pipe_fd[1]);
	waitpid(pid, NULL, 0);
	return (pipe_fd[0]);
}
