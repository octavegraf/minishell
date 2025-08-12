/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljudd <ljudd@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 16:45:12 by ljudd             #+#    #+#             */
/*   Updated: 2025/08/12 16:29:32 by ljudd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pretoken_rec(t_data *data, int *i, int *j, t_token token)
{
	while (data->inputs[*i + *j])
	{
		if (inputs[*i + *j] == '\'' || inputs[*i + *j] == '"')
			// CREATE NEW NEXT ELEM
			// ADD IT
			// SWITCH VALUES
			*i = *i + *j + 1;
			*j = 0;
			
		else
			*j++;
	}
	if (*j == 0)
	{
		// ON EST ARRIVER AU BOUT, SUPPRIMER L ELEMENT EN COURS QUI EST VIDE
	}
	else
	{
		// copie de input de i a j dans l elem, c est le dernier noeud
	}
}

void	pretokenization(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	// CREER LE PREMIER ELEM
	pretoken_rec(data, &i, &j, data->token);
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
