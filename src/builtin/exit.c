/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocgraf <ocgraf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 14:25:59 by ljudd             #+#    #+#             */
/*   Updated: 2025/08/25 16:31:40 by ocgraf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/builtin.h"

int	mini_exit(char **args)
{
	int	exit_code;

	exit_code = 0;
	if (args && args[1])
		exit_code = ft_atoi(args[1]);
	printf("exit\n");
	exit(exit_code);
	return (exit_code);
}

/* int main(void)
{
	mini_exit(0);
	return (0);
} */