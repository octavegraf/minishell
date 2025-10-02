/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocgraf <ocgraf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 14:21:51 by ljudd             #+#    #+#             */
/*   Updated: 2025/10/02 11:43:34 by ocgraf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/builtin.h"

int	mini_echo(char **args)
{
	int	i;
	int	nl;

	i = 1;
	nl = 1;
	if (args[1] && !ft_strcmp(args[1], "-n"))
	{
		nl = 0;
		i = 2;
	}
	while (args[i])
	{
		if (nl && i > 1)
			write(1, " ", 1);
		else if (!nl && i > 2)
			write(1, " ", 1);
		write(1, args[i], ft_strlen(args[i]));
		i++;
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
