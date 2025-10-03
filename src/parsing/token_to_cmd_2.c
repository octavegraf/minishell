/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_to_cmd_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljudd <ljudd@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 11:14:01 by ljudd             #+#    #+#             */
/*   Updated: 2025/10/03 11:15:53 by ljudd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	copy_args(char **res, char **vec, int count)
{
	int	i;

	i = -1;
	while (++i < count)
	{
		res[i] = ft_strdup(vec[i]);
		if (!res[i])
			clean_exit(12);
		free(vec[i]);
	}
}

/**
 * @brief Concatenate a string to the last element of the given array.
 * Create a new array and free the input one.
 * @param[in, out] vec Input array.
 * @param[in] str String to concatenate.
 * @return New array created.
 */
char	**concat_to_last_arg(char **vec, char *str)
{
	int		l;
	char	**res;

	l = 0;
	while (vec[l])
		l++;
	if (l == 0)
		return (add_to_args(vec, str));
	res = ft_calloc(l + 1, sizeof(char *));
	if (!res)
		clean_exit(12);
	copy_args(res, vec, l - 1);
	res[l - 1] = ft_strjoin(vec[l - 1], str);
	if (!res[l - 1])
		clean_exit(12);
	free(vec[l - 1]);
	free(vec);
	return (res);
}
