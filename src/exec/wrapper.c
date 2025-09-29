/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wrapper.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocgraf <ocgraf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 10:31:39 by ocgraf            #+#    #+#             */
/*   Updated: 2025/09/29 14:35:54 by ocgraf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	core_exec(t_cmd *cmd, t_env *env)
{
	if (!cmd)
		return (0);
	if (cmd->next)
		return (exec_pipeline(cmd, env));
	if (!cmd->redirs)
	{
		if (exec_decide(cmd, env))
			return (1);
	}
	else
	{
		if (exec_redirs(cmd, env))
			return (1);
	}
	return (0);
}


// TBD TBD TBD
/* main_clean_next :
	clean all the elements used between two commands
*/
void	main_clean_next(t_data *data)
{
	if (data->inputs)
	{
		free(data->inputs);
		data->inputs = NULL;
	}
	data->error_parse = false;
}

// TBD TBD TBD
/* main_loop :
	core loop used in function main, 4 parts
	- read the input
	- process the input to get the commands to execute
	- exec the commands
	- clean the elements
*/
int	main_loop(t_data *data)
{
	data->inputs = readline("minishell:");
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
		core_exec(data->cmd, data->env);
	main_clean_next(data);
	return (1);
}

// TBD TBD TBD
/* main :
	the part post loop is never supposed to happen, we exit in the loop directly
*/
int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	(void)argc;
	(void)argv;
	ft_bzero(&data, sizeof(t_data));
	data.env = get_env(envp);
	setup_signals();
	while (main_loop(&data))
		continue ;
	if (data.env)
		delete_all_env(data.env);
	return (data.exit_code);
}
