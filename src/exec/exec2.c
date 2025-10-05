/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljudd <ljudd@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 11:13:17 by ocgraf            #+#    #+#             */
/*   Updated: 2025/10/05 15:01:14 by ljudd            ###   ########.fr       */
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
