/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wrapper.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljudd <ljudd@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 10:31:39 by ocgraf            #+#    #+#             */
/*   Updated: 2025/10/05 18:35:50 by ljudd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	core_exec(t_cmd *cmd, t_env *env, t_data *data)
{
	if (!cmd)
		return (0);
	if (cmd->next)
		return (exec_pipeline(cmd, data));
	if (!cmd->cmd_path)
	{
		if (cmd->redirs)
			return (exec_redirs(cmd, env, data));
		return (0);
	}
	if (!cmd->redirs)
		return (exec_decide(cmd, env, data));
	else
		return (exec_redirs(cmd, env, data));
}

void	main_clean_next(t_data *data)
{
	if (data->inputs)
	{
		free(data->inputs);
		data->inputs = NULL;
	}
	if (data->token)
	{
		free_token(data->token);
		data->token = NULL;
	}
	if (data->cmd)
	{
		free_cmd(data->cmd);
		data->cmd = NULL;
	}
	data->error_parse = false;
}

int	main_loop(t_data *data)
{
	int	last_signal;

	data->inputs = readline("minishell: ");
	last_signal = get_last_signal();
	if (last_signal == SIGINT)
	{
		data->exit_code = 130;
		reset_signal();
	}
	if (!data->inputs)
		return (0);
	if (ft_strlen(data->inputs) == 0)
	{
		free(data->inputs);
		data->inputs = NULL;
		return (1);
	}
	add_history(data->inputs);
	core_parsing(data);
	if (!data->error_parse)
		data->exit_code = core_exec(data->cmd, data->env, data);
	else
		data->exit_code = 2;
	main_clean_next(data);
	return (1);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;
	int		exit_code;

	(void)argc;
	(void)argv;
	ft_bzero(&data, sizeof(t_data));
	data.exit_code = 0;
	data.env = get_env(envp);
	setup_signals();
	while (main_loop(&data))
		continue ;
	if (data.env)
		delete_all_env(data.env);
	exit_code = data.exit_code;
	return (exit_code);
}
