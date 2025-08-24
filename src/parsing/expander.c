/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljudd <ljudd@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 14:42:54 by ljudd             #+#    #+#             */
/*   Updated: 2025/08/24 14:43:20 by ljudd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_char(char **str, char c)
{
	char	*tmp;
	int		k;

	k = 0;
	while ((*str)[k])
		k++;
	tmp = ft_calloc(k + 2, sizeof(char));
	if (!tmp)
		clean_exit(12);
	k = -1;
	while ((*str)[++k])
		tmp[k] = (*str)[k];
	tmp[k] = c;
	free(*str);
	*str = tmp;
}

void	expand_dollar(char **res, char *inp, int *i, t_data *data)
{
	int		j;
	char	*to_find;
	t_env	*found;

	j = 0;
	while (inp[*i + j] && inp[*i + j] != ' ')
		j++;
	to_find = ft_strcpy_ij(inp, *i, j);
	*i = *i + j - 1;
	found = search_env(data->env, to_find);
	free(to_find);
	if (found)
	{
		j = -1;
		while (found->value[++j])
			add_char(res, found->value[j]);
	}
}

char	*expand_inputs(char *inp, t_data *data)
{
	int		i;
	char	*res;

	i = -1;
	res = ft_calloc(1, sizeof(char));
	while (inp[++i])
	{
		if (inp[i] == '$')
		{
			i++;
			expand_dollar(&res, inp, &i, data);
		}
		else
			add_char(&res, inp[i]);
	}
	return (res);
}

void	expand_token(t_token *token, t_data *data)
{
	char	*expanded_inp;

	if (token->quoted == '\'' || !(token->inputs))
		return ;
	expanded_inp = expand_inputs(token->inputs, data);
	free(token->inputs);
	token->inputs = expanded_inp;
}

void	expander(t_data *data)
{
	t_token	*tmp;

	tmp = data->token;
	while (tmp)
	{
		expand_token(tmp, data);
		tmp = tmp->next;
	}
}
