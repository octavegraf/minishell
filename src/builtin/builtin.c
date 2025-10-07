/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljudd <ljudd@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 17:10:08 by ocgraf            #+#    #+#             */
/*   Updated: 2025/10/06 16:10:48 by ljudd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/builtin.h"

int	is_builtin(t_cmd *cmd)
{
	if (!cmd->cmd_path)
		return (0);
	if (!ft_strcmp(cmd->cmd_path, "cd")
		|| !ft_strcmp(cmd->cmd_path, "exit")
		|| !ft_strcmp(cmd->cmd_path, "export")
		|| !ft_strcmp(cmd->cmd_path, "unset"))
		return (1);
	else if (!ft_strcmp(cmd->cmd_path, "echo")
		|| !ft_strcmp(cmd->cmd_path, "env")
		|| !ft_strcmp(cmd->cmd_path, "pwd"))
		return (2);
	return (0);
}
