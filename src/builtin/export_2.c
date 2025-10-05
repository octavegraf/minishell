/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljudd <ljudd@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 15:06:41 by ljudd             #+#    #+#             */
/*   Updated: 2025/10/05 15:07:12 by ljudd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/builtin.h"

/**
 * @brief Export environment variables.
 * @param[in, out] env Environment variables list.
 * @param[in] args Array of arguments in format "NAME=VALUE".
 * @return 0 on success, 1 on error.
 */
int	mini_export(t_env *env, char **args)
{
	int		i;
	int		has_error;

	if (!args || !**args)
		return (mini_env(env));
	i = -1;
	has_error = 0;
	while (args[++i])
	{
		if (process_export_arg(env, args[i], &has_error))
			return (1);
	}
	return (has_error);
}
