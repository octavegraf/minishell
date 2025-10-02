/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pretoken_subfunc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljudd <ljudd@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 11:48:45 by ljudd             #+#    #+#             */
/*   Updated: 2025/10/02 14:48:47 by ljudd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Add the current word as input the token and reset the word
 * length counter.
 * @param[in, out] data Inputs is used and token is created.
 * @param[in, out] i Current index in the input string.
 * @param[in, out] j Length of the current word being processed.
 * @param[in, out] token Current token being processed.
 */
void	pretoken_copy(t_data *data, int *i, int *j, t_token **token)
{
	if (*j != 0)
	{
		(*token)->inputs = ft_strcpy_ij(data->inputs, *i, *j);
		*i = *i + *j;
		*j = 0;
	}
}

/**
 * @brief Handle the operators in the input string during the pretokenization
 * phase. Two cases :
 * 
 * - If we are in a quote, we add the operator to the current word
 * 
 * - If we are not in a quote, we end the current word, create a new token
 * for the operator, set its type and redir_type if needed, create a new token
 * and continue the pretokenization.
 * 
 * @param[in, out] data Inputs is used and token is created.
 * @param[in, out] i Current index in the input string.
 * @param[in, out] j Length of the current word being processed.
 * @param[in, out] token Current token being processed.
 */
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

/**
 * @brief Handle the spaces in the input string during the pretokenization
 * phase. Two cases :
 * 
 * - If we are in a quote, we add the space to the current word
 * 
 * - If we are not in a quote, we end the current word and create a new token
 * 
 * @param[in, out] data Inputs is used and token is created.
 * @param[in, out] i Current index in the input string.
 * @param[in, out] j Length of the current word being processed.
 * @param[in, out] token Current token being processed.
 */
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

/**
 * @brief Handle the quotes in the input string during the pretokenization
 * phase. Two cases :
 * 
 * - If we are not in a quote, we start a quote and create a new token
 * 
 * - If we are in a quote and we find the closing quote, we end the quote and
 * create a new token
 * 
 * @param[in, out] data Inputs is used and token is created.
 * @param[in, out] i Current index in the input string.
 * @param[in, out] j Length of the current word being processed.
 * @param[in, out] token Current token being processed.
 */
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

/**
 * @brief Recursive function to create the list of tokens from the input
 * string.
 * 
 * @param[in, out] data Inputs is used, token is created and error_parse can
 * be set to true.
 * @param[in, out] i Current index in the input string.
 * @param[in, out] j Length of the current word being processed.
 * @param[in, out] token Current token being processed.
 */
void	pretoken_rec(t_data *data, int *i, int *j, t_token **token)
{
	if (data->inputs[*i + *j])
	{
		if (data->inputs[*i + *j] == '\'' || data->inputs[*i + *j] == '"')
			pretoken_quotes(data, i, j, token);
		else if ((data->inputs[*i + *j] == '<' || data->inputs[*i + *j] == '>'
				|| data->inputs[*i + *j] == '|') && !(*token)->quoted)
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
			parse_error(data, "parse error missing closing quote\n", NULL);
		pretoken_copy(data, i, j, token);
	}
}
