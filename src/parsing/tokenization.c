/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljudd <ljudd@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 16:15:59 by ljudd             #+#    #+#             */
/*   Updated: 2025/10/03 10:59:30 by ljudd            ###   ########.fr       */
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
		data->error_parse = true;
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
		token_deleter(data, token->next);
	}
}

/**
 * @brief Change the token list to finish the tokenization phase, two steps :
 * 
 * - First, all the empty cmd token are deleted
 * 
 * - Second, for each redirection token, we attach the next token as a target
 * 
 * @note tmp2 variable is used to keep a non null token while deleting.
 * 
 * @param[in, out] data token is modified and error_parse can be set to true.
 */
void	tokenization(t_data *data)
{
	t_token	*tmp;
	t_token	*tmp2;

	tmp = data->token;
	tmp2 = data->token;
	while (tmp)
	{
		if (tmp->type == TREE_CMD && !tmp->inputs)
			tmp = token_deleter(data, tmp);
		else
			tmp = tmp->next;
		if (tmp)
			tmp2 = tmp;
	}
	while (tmp2->past)
		tmp2 = tmp2->past;
	data->token = tmp2;
	tmp = tmp2;
	while (tmp && !data->error_parse)
	{
		if (tmp->type == TREE_REDIR)
			token_redir_target(data, tmp);
		tmp = tmp->next;
	}
}
