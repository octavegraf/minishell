/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocgraf <ocgraf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 14:21:51 by ljudd             #+#    #+#             */
/*   Updated: 2025/08/29 11:47:07 by ocgraf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/builtin.h"

int	mini_echo(char **args)
{
	int	i;
	int	nl;

	i = -1;
	nl = 1;
	while (args[++i])
	{
		if ((i == 1 && nl == 1) || i > 1)
			write(1, " ", 1);
		if (!i && !ft_strcmp(args[i], "-n"))
			nl = 0;
		else
			write(1, args[i], ft_strlen(args[i]));
	}
	if (nl)
		write(1, "\n", 1);
	return (0);
}

// int	main(int argc, char **argv)
// {
// 	mini_echo(argv + 1);
// 	(void)argc;
// 	return (0);
// }
