/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljudd <ljudd@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 16:02:26 by ljudd             #+#    #+#             */
/*   Updated: 2025/08/24 10:00:29 by ljudd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* clean_exit :
*/
// TBD TBD TBD
// 12 = MALLOC ERROR
// 8 = parsing missing closing quote
void	clean_exit(int exit_code)
{
	printf("exit\n");
	exit(exit_code);
}
