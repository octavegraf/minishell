/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocgraf <ocgraf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 14:04:31 by ocgraf            #+#    #+#             */
/*   Updated: 2025/10/02 15:28:51 by ocgraf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/exec.h"

void	setup_child(t_cmd *cmd, int prev_pipefd, int *pipefd, t_env *env)
{
	setup_child_signals();
	if (prev_pipefd >= 0)
	{
		if (dup2(prev_pipefd, STDIN_FILENO) < 0)
			exit(1);
		close(prev_pipefd);
	}
	if (cmd->next)
	{
		if (dup2(pipefd[1], STDOUT_FILENO) < 0)
			exit(1);
		close(pipefd[1]);
		close(pipefd[0]);
	}
	if (apply_redirs(cmd->redirs, 0, 0, env))
		exit(1);
	exec_function(cmd, env);
	exit(1);
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

int	exec_pipeline(t_cmd *cmd, t_env *env)
{
	int		pipefd[2];
	int		prev_pipefd;
	pid_t	pid;
	int		pid_array[100];
	int		count;
	int		status;
	int		exit_code;

	prev_pipefd = -1;
	count = 0;
	while (cmd)
	{
		if (cmd->next && pipe(pipefd) < 0)
			return (perror("pipe"), 1);
		pid = fork();
		if (pid < 0)
			return (perror("fork"), 1);
		if (pid == 0)
			setup_child(cmd, prev_pipefd, pipefd, env);
		pid_array[count++] = pid;
		close_parent_pipes(cmd, &prev_pipefd, pipefd);
		cmd = cmd->next;
	}
	if (prev_pipefd >= 0)
		close(prev_pipefd);
	exit_code = 0;
	waitpid(pid_array[count - 1], &status, 0);
	if (WIFEXITED(status))
		exit_code = WEXITSTATUS(status);
	while (--count > 0)
		waitpid(pid_array[count - 1], NULL, 0);
	return (exit_code);
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