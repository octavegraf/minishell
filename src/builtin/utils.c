/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocgraf <ocgraf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 11:15:56 by ocgraf            #+#    #+#             */
/*   Updated: 2025/08/15 12:47:57 by ocgraf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*join_args(char **args)

{
	int		i;
	char	*result;
	char	*temp;

	i = 0;
	result = ft_strdup("");
	if (!result)
		return (NULL);
	while (args[i])
	{
		temp = ft_strjoin(result, args[i]);
		free(result);
		result = temp;
		if (!result)
			return (NULL);
		i++;
	}
	return (result);
}
