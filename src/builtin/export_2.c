/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljudd <ljudd@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 15:06:41 by ljudd             #+#    #+#             */
/*   Updated: 2025/10/06 14:01:48 by ljudd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/builtin.h"

/**
 * @brief Sort string array alphabetically.
 * @param[in, out] arr Array of strings.
 * @param[in] size Size of the array.
 */
static void	sort_string_array(char **arr, int size)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (i < size - 1)
	{
		j = i + 1;
		while (j < size)
		{
			if (ft_strcmp(arr[i], arr[j]) > 0)
			{
				tmp = arr[i];
				arr[i] = arr[j];
				arr[j] = tmp;
			}
			j++;
		}
		i++;
	}
}

/**
 * @brief Print environment variables in export format.
 * @param[in] env Environment variables list.
 * @return 0 on success.
 */
static int	print_export(t_env *env)
{
	char	**arr;
	char	*equal;
	int		i;

	arr = env_to_array(env);
	if (!arr)
		return (ft_dprintf(2, "export: memory allocation failed\n"), 1);
	i = 0;
	while (arr[i])
		i++;
	sort_string_array(arr, i);
	i = 0;
	while (arr[i])
	{
		equal = ft_strchr(arr[i], '=');
		if (equal)
		{
			*equal = '\0';
			ft_printf("declare -x %s=\"%s\"\n", arr[i], equal + 1);
		}
		i++;
	}
	double_free((void **)arr);
	return (0);
}

/**
 * @brief Export environment variables.
 * @param[in, out] env_ptr Pointer to environment variables list.
 * @param[in] args Array of arguments in format "NAME=VALUE".
 * @return 0 on success, 1 on error.
 */
int	mini_export(t_env **env_ptr, char **args)
{
	int		i;
	int		has_error;

	if (!args || !args[0])
		return (print_export(*env_ptr));
	i = -1;
	has_error = 0;
	while (args[++i])
		*env_ptr = process_export_arg(*env_ptr, args[i], &has_error);
	return (has_error);
}
