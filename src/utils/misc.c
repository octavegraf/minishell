/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocgraf <ocgraf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 18:09:41 by ljudd             #+#    #+#             */
/*   Updated: 2025/10/01 11:51:57 by ocgraf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// A REMPLACER PAR SUBSTR

/**
 * @brief Copy a substring from src, starting at index i and of length j.
 * @param[in] src Source string.
 * @param[in] i Starting index.
 * @param[in] j Length of the substring.
 * @return char* New string created.
 */
char	*ft_strcpy_ij(char *src, int i, int j)
{
	int		k;
	char	*res;

	res = ft_calloc(j + 1, sizeof(char));
	if (!res)
		clean_exit(12);
	k = -1;
	while (++k < j)
	{
		res[k] = src[i + k];
	}
	res[k] = '\0';
	return (res);
}
