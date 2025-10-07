/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljudd <ljudd@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 16:15:59 by ljudd             #+#    #+#             */
/*   Updated: 2025/10/06 16:37:53 by ljudd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Delete the current token and adjust accordingly the previous and next.
 * Preserves the space_before flag by transferring it to the next token.
 * @param[out] data error_parse is set to true if the list is empty after
 * the deletion.
 * @param[in, out] token token to delete.
 * @return t_token* next token after the deletion.
 */
t_token	*token_deleter(t_data *data, t_token *token)
{
	t_token	*res;

	if (token->next)
	{
		token->next->past = token->past;
		if (token->space_before)
			token->next->space_before = true;
	}
	if (token->past)
		token->past->next = token->next;
	res = token->next;
	if (!token->next && !token->past)
		data->token = NULL;
	if (token->inputs)
		free(token->inputs);
	if (token->target)
		free(token->target);
	free(token);
	return (res);
}

/**
 * @brief Add the next token as a target to the current redirection token and
 * delete the next token from the list.
 * @param[out] data error_parse is set to true if the next token is a 
 * redirection or a pipe.
 * @param[in, out] token Redirection token to which we want to add a target.
 */
void	token_redir_target(t_data *data, t_token *token)
{
	if (!token->next || token->next->type != TREE_CMD)
		parse_error(data, NULL, token);
	else
	{
		token->target = token->next->inputs;
		token->next->inputs = NULL;
		token_deleter(data, token->next);
	}
}

static void	fix_null_quoted_tokens(t_data *data)
{
	t_token	*tmp;

	tmp = data->token;
	while (tmp)
	{
		if (tmp->quoted && !tmp->inputs)
		{
			tmp->inputs = ft_strdup("");
			if (!tmp->inputs)
				clean_exit(data, 12);
		}
		tmp = tmp->next;
	}
}

static void	delete_empty_tokens(t_data *data, t_token **last_valid)
{
	t_token	*tmp;

	tmp = data->token;
	*last_valid = NULL;
	while (tmp)
	{
		if (tmp->type == TREE_CMD && !tmp->quoted
			&& (!tmp->inputs || tmp->inputs[0] == '\0'))
		{
			if (tmp == data->token)
				data->token = tmp->next;
			tmp = token_deleter(data, tmp);
		}
		else
		{
			*last_valid = tmp;
			tmp = tmp->next;
		}
	}
}

/**
 * @brief Change the token list to finish the tokenization phase, two steps :
 * - First, all the empty cmd token are deleted
 * - Second, for each redirection token, we attach the next token as a target
 * @param[in, out] data token is modified and error_parse can be set to true.
 */
void	tokenization(t_data *data)
{
	t_token	*tmp;
	t_token	*last_valid;

	last_valid = NULL;
	fix_null_quoted_tokens(data);
	delete_empty_tokens(data, &last_valid);
	if (data->error_parse)
		return ;
	if (!data->error_parse)
		merge_adjacent_tokens(data);
	tmp = data->token;
	while (tmp && !data->error_parse)
	{
		if (tmp->type == TREE_REDIR)
			token_redir_target(data, tmp);
		tmp = tmp->next;
	}
}
