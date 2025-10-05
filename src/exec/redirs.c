/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljudd <ljudd@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 17:45:17 by ocgraf            #+#    #+#             */
/*   Updated: 2025/10/05 18:23:20 by ljudd            ###   ########.fr       */
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

int	apply_redirs(t_redir *redirs, t_env *env, t_data *data)
{
	int	fd;
	int	should_apply;

	while (redirs)
	{
		fd = open_redir_fd(redirs, env, data);
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

	pid = fork();
	if (pid < 0)
		return (perror("fork"), 1);
	if (pid == 0)
	{
		if (apply_redirs(cmd->redirs, env, data))
			clean_exit(data, 1);
		clean_exit(data, exec_function(cmd, env, data));
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
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