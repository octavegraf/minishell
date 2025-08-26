/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocgraf <ocgraf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 14:21:51 by ljudd             #+#    #+#             */
/*   Updated: 2025/08/26 17:46:51 by ocgraf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/builtin.h"

int	disable_nl(char *prompt)
{	
	int	i;

	i = 1;
	while (prompt[++i])
	{
		if (prompt[i] != 'n')
			return (0);
	}
	return (1);
}

int	mini_echo(char **args)
{
	int	i;
	int	nl;
	int	to_print;

	i = -1;
	nl = 1;
	while (args[++i])
	{
		to_print = 1;
		if (!ft_strncmp(args[i], "-n", 2))
		{
			if (disable_nl(args[i]))
			{
				nl = 0;
				to_print = 0;
			}
		}
		if (i != 0 && args[i] && to_print)
			write(1, " ", 1);
		if (to_print)
			printf("%s", args[i]);
	}
	if (nl)
		write(1, "\n", 1);
	return (0);
}

/* int	main(int argc, char **argv)
{
	mini_echo(argv + 1);
	(void)argc;
	return (0);
} */
