/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocgraf <ocgraf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 14:21:51 by ljudd             #+#    #+#             */
/*   Updated: 2025/08/13 14:41:06 by ocgraf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	mini_echo(char **prompt)
{
	int	i;
	int	nl;
	int	to_print;

	i = -1;
	nl = 1;
	while (prompt[++i])
	{
		to_print = 1;
		if (!ft_strncmp(prompt[i], "-n", 2))
		{
			if (disable_nl(prompt[i]))
			{
				nl = 0;
				to_print = 0;
			}
		}
		if (i != 0 && prompt[i] && to_print)
			write(1, " ", 1);
		if (to_print)
			ft_printf("%s", prompt[i]);
	}
	if (nl)
		write(1, "\n", 1);
}

/* int	main(int argc, char **argv)
{
	mini_echo(argv + 1);
	(void)argc;
	return (0);
} */
