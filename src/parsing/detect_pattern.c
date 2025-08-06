/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   detect_pattern.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocgraf <ocgraf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 14:10:53 by ocgraf            #+#    #+#             */
/*   Updated: 2025/08/06 15:55:12 by ocgraf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/* char	*start_pattern(const char *str, char *pattern)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	while (str[++i])
	{
		if (pattern[j] == '*' && pattern[j + 1] != '*')
			wildcard_skipper(i, j, str, pattern);
	}
	return (NULL);
}

void	wildcard_skipper(int i, int j, const char *str, char *pattern)
{
	while (str[i] && str[i] != pattern[j + 1])
		i++;
	j++;
}
 */
/*
	Usage : * = wildcard. Use '**' to detect '*'
	Return : pointer to first detected pattern, NULL
	Example: str = "I love $(FOOD) and beers.", pattern = "$(*)".
		Will return : "$(FOOD) and beers"
*/
