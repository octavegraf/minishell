/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljudd <ljudd@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 16:45:12 by ljudd             #+#    #+#             */
/*   Updated: 2025/10/06 10:29:49 by ljudd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Copy a substring from src, starting at index i and of length j.
 * @param[in] src Source string.
 * @param[in] i Starting index.
 * @param[in] j Length of the substring.
 * @param[in] data Data structure for clean_exit if malloc fails.
 * @return char* New string created.
 */
char	*ft_strcpy_ij(char *src, int i, int j, t_data *data)
{
	int		k;
	char	*res;

	res = ft_calloc(j + 1, sizeof(char));
	if (!res)
		clean_exit(data, 12);
	k = -1;
	while (++k < j)
	{
		res[k] = src[i + k];
	}
	res[k] = '\0';
	return (res);
}

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
		token_to_cmd(data);
}
