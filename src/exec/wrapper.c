/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wrapper.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocgraf <ocgraf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 10:31:39 by ocgraf            #+#    #+#             */
/*   Updated: 2025/09/03 11:53:41 by ocgraf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	core_exec(t_cmd *cmd, t_env *env)
{
	while (cmd)
	{
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
		cmd = cmd->next;
	}
	return (0);
}


// TBD TBD TBD
/* main_clean_next :
	clean all the elements used between two commands
*/
void	main_clean_next(t_data *data)
{
	// TBD TBD TBD
	data->error_parse = false;
	return ;
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
	// prompt ? necessaire a gerer ? "minishell ATM"
	data->inputs = readline("minishell:");
	// precaution a prendre relative au readline ?
	// readline vide a convertir en \n ?
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

	(void) argc;
	(void) argv;
	(void) envp;
	ft_bzero(&data, sizeof(t_data));
	data.env = get_env(envp);
	while (main_loop(&data))
		continue ;
	// fonction free_all
	return (data.exit_code);
}
