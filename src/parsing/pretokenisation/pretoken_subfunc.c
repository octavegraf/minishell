/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pretoken_subfunc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljudd <ljudd@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 11:48:45 by ljudd             #+#    #+#             */
/*   Updated: 2025/08/24 11:49:58 by ljudd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pretoken_copy(t_data *data, int *i, int *j, t_token **token)
{
	if (*j != 0)
	{
		(*token)->inputs = ft_strcpy_ij(data->inputs, *i, *j);
		*i = *i + *j;
		*j = 0;
	}
}

void	pretoken_ope(t_data *data, int *i, int *j, t_token **token)
{
	pretoken_copy(data, i, j, token);
	(*token)->next = token_new(NULL, (*token)->quoted, NULL, *token);
	(*token) = (*token)->next;
	(*token)->type = TREE_REDIR;
	if (data->inputs[*i] == '<' && data->inputs[*i + 1] == '<')
	{
		(*token)->redir_type = REDIR_HEREDOC;
		(*i)++;
	}
	else if (data->inputs[*i] == '<')
		(*token)->redir_type = REDIR_IN;
	else if (data->inputs[*i] == '>' && data->inputs[*i + 1] == '>')
	{
		(*token)->redir_type = REDIR_APPEND;
		(*i)++;
	}
	else if (data->inputs[*i] == '>')
		(*token)->redir_type = REDIR_OUT;
	else if (data->inputs[*i] == '|')
		(*token)->type = TREE_PIPE;
	(*i)++;
	(*token)->next = token_new(NULL, (*token)->quoted, NULL, *token);
	(*token) = (*token)->next;
	pretoken_rec(data, i, j, token);
}

void	pretoken_space(t_data *data, int *i, int *j, t_token **token)
{
	if ((*token)->quoted)
		(*j)++;
	else
	{
		pretoken_copy(data, i, j, token);
		(*token)->next = token_new(NULL, (*token)->quoted, NULL, *token);
		(*token) = (*token)->next;
		(*i)++;
	}
	pretoken_rec(data, i, j, token);
}

void	pretoken_quotes(t_data *data, int *i, int *j, t_token **token)
{
	if ((*token)->quoted == '\0')
	{
		pretoken_copy(data, i, j, token);
		(*token)->next = token_new(NULL, data->inputs[*i], NULL, *token);
		(*token) = (*token)->next;
		(*i)++;
	}
	else if ((*token)->quoted == data->inputs[*i + *j])
	{
		pretoken_copy(data, i, j, token);
		(*token)->next = token_new(NULL, '\0', NULL, *token);
		(*token) = (*token)->next;
		(*i)++;
	}
	else
		(*j)++;
	pretoken_rec(data, i, j, token);
}

void	pretoken_rec(t_data *data, int *i, int *j, t_token **token)
{
	if (data->inputs[*i + *j])
	{
		if (data->inputs[*i + *j] == '\'' || data->inputs[*i + *j] == '"')
			pretoken_quotes(data, i, j, token);
		else if (data->inputs[*i + *j] == '<' || data->inputs[*i + *j] == '>'
			|| data->inputs[*i + *j] == '|')
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
	{
		if ((*token)->quoted)
			parse_error(data, "Parsing Error: missing closing quote\n");
		pretoken_copy(data, i, j, token);
	}
}
