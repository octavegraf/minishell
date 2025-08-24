/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljudd <ljudd@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 16:15:59 by ljudd             #+#    #+#             */
/*   Updated: 2025/08/24 16:18:23 by ljudd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*token_deleter(t_data *data, t_token *token)
{
	t_token	*res;

	if (token->next)
		token->next->past = token->past;
	if (token->past)
		token->past->next = token->next;
	res = token->next;
	if (!token->next && !token->past)
		data->error_parse = true;
	free(token);
	return (res);
}

void	token_redir_target(t_data *data, t_token *token)
{
	if (!token->next || token->next->type != TREE_CMD)
	{
		data->error_parse = true;
		if (token->redir_type == REDIR_IN)
			parse_error(data, "parse error near `<'\n");
		else if (token->redir_type == REDIR_OUT)
			parse_error(data, "parse error near `>'\n");
		else if (token->redir_type == REDIR_APPEND)
			parse_error(data, "parse error near `>>'\n");
		else if (token->redir_type == REDIR_HEREDOC)
			parse_error(data, "parse error near `<<'\n");
	}
	else
	{
		token->target = token->next->inputs;
		token_deleter(data, token->next);
	}
}

void	tokenization(t_data *data)
{
	t_token	*tmp;

	tmp = data->token;
	while (tmp)
	{
		if (tmp->type == TREE_CMD && !tmp->inputs)
		{
			tmp = token_deleter(data, tmp);
		}
		else
			tmp = tmp->next;
	}
	tmp = data->token;
	while (tmp && !data->error_parse)
	{
		if (tmp->type == TREE_REDIR)
			token_redir_target(data, tmp);
		tmp = tmp->next;
	}
}
