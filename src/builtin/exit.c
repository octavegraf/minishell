/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocgraf <ocgraf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 14:25:59 by ljudd             #+#    #+#             */
/*   Updated: 2025/09/30 15:22:40 by ocgraf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/builtin.h"

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

int	mini_exit(char **args)
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
			exit(2);
		}
		exit_code = ft_atoi(args[1]);
	}
	exit(exit_code);
	return (exit_code);
}

/* int main(void)
{
	mini_exit(0);
	return (0);
} */