/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocgraf <ocgraf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 17:10:08 by ocgraf            #+#    #+#             */
/*   Updated: 2025/08/24 17:21:46 by ocgraf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/builtin.h"

int	is_builtin(t_cmd *cmd)
{
	if (!ft_strcmp(cmd->cmd_path, "cd")
		|| !ft_strcmp(cmd->cmd_path, "echo")
		|| !ft_strcmp(cmd->cmd_path, "env")
		|| !ft_strcmp(cmd->cmd_path, "exit")
		|| !ft_strcmp(cmd->cmd_path, "export")
		|| !ft_strcmp(cmd->cmd_path, "pwd")
		|| !ft_strcmp(cmd->cmd_path, "unset"))
		return (1);
	return (0);
}

