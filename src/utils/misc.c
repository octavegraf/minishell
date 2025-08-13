/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljudd <ljudd@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 18:09:41 by ljudd             #+#    #+#             */
/*   Updated: 2025/08/13 19:19:50 by ljudd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* ft_strcpy_ij :
	copy j elements from the array starting at index i end on a \0
	return the array created
	use with caution, it supposes we don't go below strlen with the choice of 
		i and j
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
