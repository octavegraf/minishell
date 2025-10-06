/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljudd <ljudd@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 14:25:59 by ljudd             #+#    #+#             */
/*   Updated: 2025/10/06 10:59:34 by ljudd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/builtin.h"

/**
 * @brief Free all allocated memory and exit the program.
 * 
 * @param[in] data Data structure containing all allocated memory to free.
 * @param[in] exit_code Exit code of the program.
 * 12 = MALLOC ERROR
 * 11 = ERROR PARSING EXIT CODE
 * 8 = parsing missing closing quote
 */
void	clean_exit(t_data *data, int exit_code)
{
	if (data->inputs)
		free(data->inputs);
	if (data->token)
		free_token(data->token);
	if (data->cmd)
		free_cmd(data->cmd);
	if (data->env)
		delete_all_env(data->env);
	clear_history();
	exit(exit_code);
}

int	is_valid_number(char *str)
{
	int	i;

	if (!str || !*str)
		return (0);
	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	mini_exit(char **args, t_data *data)
{
	int	exit_code;

	printf("exit\n");
	exit_code = 0;
	if (args && args[1])
	{
		if (args[2])
		{
			ft_dprintf(2, "exit: too many arguments\n");
			return (1);
		}
		if (!is_valid_number(args[1]))
		{
			ft_dprintf(2, "exit: %s: numeric argument required\n", args[1]);
			clean_exit(data, 2);
		}
		exit_code = ft_atoi(args[1]);
	}
	clean_exit(data, exit_code);
	return (exit_code);
}

/* int main(void)
{
	mini_exit(0);
	return (0);
} */