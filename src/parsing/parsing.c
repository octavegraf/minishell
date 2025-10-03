/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljudd <ljudd@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 16:45:12 by ljudd             #+#    #+#             */
/*   Updated: 2025/10/03 10:56:36 by ljudd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Parsing of the input string, to reach the command list used in the
 * execution phase. Four steps :
 * 
 * - First, the input string is split into tokens (pretokenization phase)
 * 
 * - Second, the tokens are expanded (expansion phase)
 * 
 * - Third, the tokens are modified (tokenization phase)
 * 
 * - Fourth, the command list is created (token to cmd phase)
 * 
 * @param[in,out] data Input is used, token and cmd are created and error_parse
 * is modified if an error happens.
 */
void	core_parsing(t_data *data)
{
	pretokenization(data);
	if (!data->error_parse)
		expander(data);
	if (!data->error_parse)
		tokenization(data);
	if (!data->error_parse)
		merge_adjacent_tokens(data);
	if (!data->error_parse)
		token_to_cmd(data);
}
