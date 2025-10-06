/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocgraf <ocgraf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 11:13:17 by ocgraf            #+#    #+#             */
/*   Updated: 2025/10/06 14:05:16 by ocgraf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/exec.h"

int	exec_function(t_cmd *cmd, t_env *env, t_data *data)
{
	if (is_builtin(cmd))
		return (exec_builtin(cmd, env, data));
	if (!is_builtin(cmd))
		return (exec_external(cmd, env, data));
	return (1);
}

int	exec_decide(t_cmd *cmd, t_env *env, t_data *data)
{
	if (is_builtin(cmd) == 2 || !is_builtin(cmd))
		return (exec_in_child(cmd, env, data));
	else
		return (exec_builtin(cmd, env, data));
	return (0);
}

int	count_cmd(t_cmd *cmd)
{
	int	count;

	count = 0;
	if (!cmd || !cmd->args)
		return (count);
	while (cmd)
	{
		count++;
		cmd = cmd->next;
	}
	return (count);
}
