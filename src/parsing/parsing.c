/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljudd <ljudd@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 16:45:12 by ljudd             #+#    #+#             */
/*   Updated: 2025/08/24 11:49:03 by ljudd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// TBD
void	expander(t_data *data)
{
	(void) data;
	return ;
}

// TBD
void	tokenization(t_data *data)
{
	(void) data;
	return ;
}

// TBD
void	token_to_tree(t_data *data)
{
	(void) data;
	return ;
}

// TBD
void	tree_to_cmd(t_data *data)
{
	(void) data;
	return ;
}

/* core_parsing :
	parsing that transform the char *input into a list of t_cmd,
	- splitting for pretokenization
	- expander for $ variable (not between quotes)
	- tokenization
	- creation of the tree based on tokenization
	- tree conversion into the list of cmds used for the exec
*/
void	core_parsing(t_data *data)
{
	pretokenization(data);
	if (!data->error_parse)
		expander(data);
	if (!data->error_parse)
		tokenization(data);
	if (!data->error_parse)
		token_to_tree(data);
	if (!data->error_parse)
		tree_to_cmd(data);
}
