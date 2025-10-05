/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljudd <ljudd@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 12:22:07 by ljudd             #+#    #+#             */
/*   Updated: 2025/10/05 14:02:45 by ljudd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Add the exit code to the result string, starting from the index i.
 * 
 * @param[out] res Output string where the exit code is added.
 * @param[in] data Fetch the exit code.
 */
void	add_exit(char **res, t_data *data)
{
	char	*exit_str;
	int		j;

	j = 0;
	exit_str = ft_itoa(data->exit_code);
	if (!exit_str)
	{
		add_char(res, '0', data);
		return ;
	}
	while (exit_str[j])
	{
		add_char(res, exit_str[j], data);
		j++;
	}
	free(exit_str);
}

/**
 * @brief Add a string to the end of a string. Create a new string and free
 * the input one.
 * 
 * @param[in, out] str Pointer to the string we modify.
 * @param[in] to_add String to add.
 * @param[in] data Data structure for clean_exit if malloc fails.
 */
void	add_str(char **str, char *to_add, t_data *data)
{
	int		j;

	j = 0;
	while (to_add[j])
	{
		add_char(str, to_add[j], data);
		j++;
	}
}
