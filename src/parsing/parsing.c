/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljudd <ljudd@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 16:45:12 by ljudd             #+#    #+#             */
/*   Updated: 2025/08/13 19:14:55 by ljudd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*token_new(char *inputs, char quoted, t_token *next, t_token *past)
{
	t_token	*res;

	res = ft_calloc(1, sizeof(t_token));
	if (!res)
		clean_exit(12);
	res->inputs = inputs;
	res->quoted = quoted;
	res->next = next;
	res->past = past;
	return (res);
}

// TBD pretoken_quotes
void	pretoken_quotes(t_data *data, int *i, int *j, t_token *token)
{
	(void) data;
	(void) i;
	(void) j;
	(void) token;
	return ;
}

// TBD pretoken_ope
void	pretoken_ope(t_data *data, int *i, int *j, t_token *token)
{
	(void) data;
	(void) i;
	(void) j;
	(void) token;
	return ;
}

// TBD pretoken_space
void	pretoken_space(t_data *data, int *i, int *j, t_token *token)
{
	(void) data;
	(void) i;
	(void) j;
	(void) token;
	return ;
}

void	pretoken_copy(t_data *data, int *i, int *j, t_token *token)
{
	if (*j != 0)
	{
		token->inputs = ft_strcpy_ij(data->inputs, *i, *j);
		*i = *i + *j;
		*j = 0;
	}
	else if (token->past)
	{
		token = token->past;
		free(token->next->inputs);
		free(token->next);
		token->next = NULL;
	}
}

void	pretoken_rec(t_data *data, int *i, int *j, t_token *token)
{
	if (data->inputs[*i + *j])
	{
		if (data->inputs[*i + *j] == '\'' || data->inputs[*i + *j] == '"')
			pretoken_quotes(data, i, j, token);
		else if (1)
			pretoken_ope(data, i, j, token);
		else if (data->inputs[*i + *j] == ' ')
			pretoken_space(data, i, j, token);
		else
		{
			(*j)++;
			pretoken_rec(data, i, j, token);
		}
	}
	else
		pretoken_copy(data, i, j, token);
}

void	pretokenization(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	data->token = token_new(NULL, '\0', NULL, NULL);
	pretoken_rec(data, &i, &j, data->token);
}

// TBD
void	expander(t_data *data)
{
	(void) data;
	return ;
}

// TBD
void	tokenization(t_data *data)
{
	(void) data;
	return ;
}

// TBD
void	token_to_tree(t_data *data)
{
	(void) data;
	return ;
}

// TBD
void	tree_to_cmd(t_data *data)
{
	(void) data;
	return ;
}

/* core_parsing :
	parsing that transform the char *input into a list of t_cmd,
	- splitting for pretokenization
	- expander for $ variable (not between quotes)
	- tokenization
	- creation of the tree based on tokenization
	- tree conversion into the list of cmds used for the exec
*/
void	core_parsing(t_data *data)
{
	pretokenization(data);
	if (!data->error_parse)
		expander(data);
	if (!data->error_parse)
		tokenization(data);
	if (!data->error_parse)
		token_to_tree(data);
	if (!data->error_parse)
		tree_to_cmd(data);
}
