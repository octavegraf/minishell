/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocgraf <ocgraf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 11:13:17 by ocgraf            #+#    #+#             */
/*   Updated: 2025/10/03 11:13:49 by ocgraf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/exec.h"

int	exec_function(t_cmd *cmd, t_env *env)
{
	if (is_builtin(cmd))
		return (exec_builtin(cmd, env));
	if (!is_builtin(cmd))
		return (exec_external(cmd, env));
	return (1);
}

int	exec_decide(t_cmd *cmd, t_env *env)
{
	if (is_builtin(cmd) == 2 || !is_builtin(cmd))
		return (exec_in_child(cmd, env));
	else
		return (exec_builtin(cmd, env));
	return (0);
}
