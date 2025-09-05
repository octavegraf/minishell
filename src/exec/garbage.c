/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocgraf <ocgraf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 11:13:37 by ocgraf            #+#    #+#             */
/*   Updated: 2025/09/03 11:27:06 by ocgraf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/exec.h"

// void	garbage_collector(t_data *data)
// {
// 	if (!data)
// 		return ;
// 	double_free((void **)data->env);
// 	double_free((void **)data->tokens);
// 	double_free((void **)data->cmds);
// 	free(data);
// }