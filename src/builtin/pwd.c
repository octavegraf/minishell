/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljudd <ljudd@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 14:26:53 by ljudd             #+#    #+#             */
/*   Updated: 2025/08/13 14:52:41 by ljudd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	mini_pwd(void)
{
	char	path[1024];

	if (!getcwd(path, 1024))
	{
		perror("pwd");
		return (1);
	}
	ft_printf("%s\n", path);
	return (0);
}

/* int main(void)
{
	mini_pwd();
	return (0);
} */