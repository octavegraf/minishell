/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pretoken.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljudd <ljudd@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 11:47:52 by ljudd             #+#    #+#             */
/*   Updated: 2025/08/24 11:52:31 by ljudd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pretokenization(t_data *data)
{
	int		i;
	int		j;
	t_token	*tmp;

	i = 0;
	j = 0;
	data->token = token_new(NULL, '\0', NULL, NULL);
	tmp = data->token;
	pretoken_rec(data, &i, &j, &tmp);
}
