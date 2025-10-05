/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljudd <ljudd@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 14:42:54 by ljudd             #+#    #+#             */
/*   Updated: 2025/10/05 14:02:46 by ljudd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Add a character to the end of a string. Create a new string and free
 * the input one.
 * @param[in, out] str Pointer to the string we modify.
 * @param[in] c Character to add.
 */
void	add_char(char **str, char c, t_data *data)
{
	char	*tmp;
	int		k;

	k = 0;
	while ((*str)[k])
		k++;
	tmp = ft_calloc(k + 2, sizeof(char));
	if (!tmp)
		clean_exit(data, 12);
	k = -1;
	while ((*str)[++k])
		tmp[k] = (*str)[k];
	tmp[k] = c;
	free(*str);
	*str = tmp;
}

/**
 * @brief Expand a variable in a string, starting from the index i.
 * 
 * @param[out] res Output string where the expansion is added.
 * @param[in] inp Input string containing the variable to expand.
 * @param[in, out] i Current index in inp, is updated to the end of the
 * variable name.
 * @param[in] data Fetch the env list to find the variable.
 */
void	expand_dollar(char **res, char *inp, int *i, t_data *data)
{
	int		j;
	char	*to_find;
	t_env	*found;

	if (!inp[*i])
		return (add_char(res, '$', data));
	if (inp[*i] == '?')
		return (add_exit(res, data));
	if (!(ft_isalpha(inp[*i]) || inp[*i] == '_'))
	{
		add_char(res, '$', data);
		(*i)--;
		return ;
	}
	j = 1;
	while (inp[*i + j] && (ft_isalnum(inp[*i + j]) || inp[*i + j] == '_'))
		j++;
	to_find = ft_strcpy_ij(inp, *i, j, data);
	*i = *i + j - 1;
	found = search_env(data->env, to_find);
	free(to_find);
	if (found)
		add_str(res, found->value, data);
}

/**
 * @brief Expand all the variables in a string.
 * 
 * @param[in] inp Input string to expand.
 * @param[in] data Fetch the env list to find the variables.
 * @return char* String after expansion.
 */
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
			if (!inp[i])
				break ;
		}
		else
			add_char(&res, inp[i], data);
	}
	return (res);
}

/**
 * @brief Expand all the variables in a token inputs. Do nothing if the token
 * is single quoted
 * 
 * @param[in, out] token Token to expand. Freed and replaced if expanded.
 * @param[in] data Fetch the env list to find the variables.
 */
void	expand_token(t_token *token, t_data *data)
{
	char	*expanded_inp;

	if (token->quoted == '\'' || !(token->inputs))
		return ;
	expanded_inp = expand_inputs(token->inputs, data);
	free(token->inputs);
	token->inputs = expanded_inp;
}

/**
 * @brief Expand all the tokens in the token list.
 * 
 * @param[in, out] data token list is modified.
 */
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
