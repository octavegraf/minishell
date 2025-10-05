/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljudd <ljudd@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 16:02:26 by ljudd             #+#    #+#             */
/*   Updated: 2025/10/05 13:48:20 by ljudd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* clean_exit :
*/
// TBD TBD TBD
// 12 = MALLOC ERROR
// 11 = ERROR PARSING EXIT CODE
// 8 = parsing missing closing quote
void	clean_exit(t_data *data, int exit_code)
{
	if (data->inputs)
		free(data->inputs);
	if (data->token)
		free_token(data->token);
	if (data->cmd)
		free_cmd(data->cmd);
	if (data->env)
		delete_all_env(data->env);
	clear_history();
	exit(exit_code);
}
