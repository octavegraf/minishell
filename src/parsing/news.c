/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   news.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljudd <ljudd@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 14:33:30 by ljudd             #+#    #+#             */
/*   Updated: 2025/08/25 15:56:47 by ljudd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Create a new token structure.
 * @param[in] inputs Inputs of the token.
 * @param[in] quoted Whether the token is quoted or not. ' or " or \0 if 
 * not quoted.
 * @param[in] next Next token in the list.
 * @param[in] past Previous token in the list.
 * @return t_token* New token created.
 */
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

/**
 * @brief Create a new empty command structure.
 * @note res->args is initialized as an array with one NULL element.
 * @return t_cmd* New command created.
 */
t_cmd	*new_cmd(void)
{
	t_cmd	*res;

	res = ft_calloc(1, sizeof(t_cmd));
	if (!res)
		clean_exit(12);
	res->args = ft_calloc(1, sizeof(char *));
	if (!res->args)
		clean_exit(12);
	return (res);
}

/**
 * @brief Create a new redirection structure from a token.
 * @param[in] token Token from which we want to create a redirection.
 * @return t_redir* Redirection created.
 */
t_redir	*new_redir(t_token *token)
{
	t_redir	*res;

	res = ft_calloc(1, sizeof(t_redir));
	if (!res)
		clean_exit(12);
	res->type = token->redir_type;
	res->target = ft_strdup(token->target);
	if (!res->target)
		clean_exit(12);
	return (res);
}
