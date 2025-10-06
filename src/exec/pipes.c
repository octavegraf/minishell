/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocgraf <ocgraf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 14:04:31 by ocgraf            #+#    #+#             */
/*   Updated: 2025/10/06 14:15:54 by ocgraf           ###   ########.fr       */
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
	if (apply_redirs(cmd->redirs, data->env, data))
		clean_exit(data, 1);
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

int	exec_pipeline(t_cmd *cmd, t_data *data, int count)
{
	int		pipefd[2];
	int		prev_pipefd;
	pid_t	pid;
	int		pid_array[100];

	prev_pipefd = -1;
	count = 0;
	if (count_cmd(cmd) > 100)
		return (ft_dprintf(2, "Too many commands in pipeline (>= 100)\n"));
	while (cmd)
	{
		if (cmd->next && pipe(pipefd) < 0)
			return (perror("pipe"), 1);
		pid = fork();
		if (pid < 0)
			return (perror("fork"), 1);
		if (pid == 0)
			setup_child(cmd, prev_pipefd, pipefd, data);
		pid_array[count++] = pid;
		close_parent_pipes(cmd, &prev_pipefd, pipefd);
		cmd = cmd->next;
	}
	if (prev_pipefd >= 0)
		close(prev_pipefd);
	return (wait_pipeline_processes(pid_array, count));
}

/* int	main(int argc, char **argv, char **envp)
{
	t_cmd	cmd1;
	t_cmd	cmd2;
	t_cmd	cmd3;
	t_env	*env;
	char	*args1[] = {"ls", "-la", NULL};
	char	*args2[] = {"grep", ".c", NULL};
	char	*args3[] = {"wc", "-l", NULL};

	(void)argc;
	(void)argv;
	env = get_env(envp);
	cmd1.args = args1;
	cmd1.cmd_path = "ls";
	cmd1.redirs = NULL;
	cmd1.next = &cmd2;
	cmd2.args = args2;
	cmd2.cmd_path = "grep";
	cmd2.redirs = NULL;
	cmd2.next = &cmd3;
	cmd3.args = args3;
	cmd3.cmd_path = "wc";
	cmd3.redirs = NULL;
	cmd3.next = NULL;
	printf("Test pipeline: ls -la | grep .c | wc -l\n");
	exec_pipeline(&cmd1, env);
	delete_all_env(env);
	return (0);
}
 */