/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_adjacent.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljudd <ljudd@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 11:03:39 by ljudd             #+#    #+#             */
/*   Updated: 2025/10/03 11:14:18 by ljudd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	merge_token_with_next(t_token *cur)
{
	t_token	*next;
	char	*merged;

	next = cur->next;
	merged = ft_strjoin(cur->inputs, next->inputs);
	if (!merged)
		clean_exit(12);
	free(cur->inputs);
	cur->inputs = merged;
	cur->next = next->next;
	if (next->next)
		next->next->past = cur;
	free(next->inputs);
	free(next->target);
	free(next);
}

/**
 * @brief Merge consecutive CMD tokens that are not separated by a space.
 * This handles cases like echo hello'world' or echo hello""world where
 * quotes should not introduce spaces.
 * 
 * @param[in, out] data Token list is modified.
 */
void	merge_adjacent_tokens(t_data *data)
{
	t_token	*cur;

	cur = data->token;
	while (cur)
	{
		if (cur->type == TREE_CMD && cur->inputs && cur->next
			&& cur->next->type == TREE_CMD && cur->next->inputs
			&& !cur->next->space_before)
			merge_token_with_next(cur);
		else
			cur = cur->next;
	}
}
