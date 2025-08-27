/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocgraf <ocgraf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 17:45:17 by ocgraf            #+#    #+#             */
/*   Updated: 2025/08/27 17:15:56 by ocgraf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/exec.h"

int	redirs(t_cmd cmd)
{
	while (cmd.cmd_path)
	{
		if (cmd.redirs)
		{
			if (exec_redirs(cmd))
				return (1);
		}
	}
	return (0);
}

