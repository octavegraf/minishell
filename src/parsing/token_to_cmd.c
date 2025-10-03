/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_to_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljudd <ljudd@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 14:31:21 by ljudd             #+#    #+#             */
/*   Updated: 2025/10/03 11:00:13 by ljudd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Convert a command token into a command. Add the input to the args and
 * set cmd_path if not already set.
 * If space_before is false, concatenate with the last argument.
 * 
 * @param[in] token Token to convert.
 * @param[in, out] cmd Current command to which we add the argument.
 */
void	token_convert_cmd(t_token *token, t_cmd **cmd)
{
	int	args_count;

	args_count = 0;
	while ((*cmd)->args[args_count])
		args_count++;
	if (token->space_before || args_count == 0)
	{
		if (!((*cmd)->cmd_path))
		{
			(*cmd)->cmd_path = ft_strdup(token->inputs);
			if (!((*cmd)->cmd_path))
				clean_exit(12);
		}
		(*cmd)->args = add_to_args((*cmd)->args, token->inputs);
	}
	else
		(*cmd)->args = concat_to_last_arg((*cmd)->args, token->inputs);
}

/**
 * @brief Convert a redirection token into a redirection in the current command.
 * 
 * @param[in] token Token to convert.
 * @param[in, out] cmd Current command to which we add the redirection.
 */
void	token_convert_redir(t_token *token, t_cmd **cmd)
{
	t_redir	*add_redir;
	t_redir	*last_redir;

	add_redir = new_redir(token);
	last_redir = (*cmd)->redirs;
	while (last_redir && last_redir->next)
		last_redir = last_redir->next;
	if (!last_redir)
		(*cmd)->redirs = add_redir;
	else
		last_redir->next = add_redir;
}

/**
 * @brief Convert a pipe token into a new command in the command list.
 * 
 * @param[in, out] cmd Current command to which we add a new command.
 */
void	token_convert_pipe(t_cmd **cmd)
{
	t_cmd	*add_cmd;

	add_cmd = new_cmd();
	(*cmd)->next = add_cmd;
	*cmd = add_cmd;
}

/**
 * @brief Convert a token depending on its type and the last treated token in
 * a command.
 * 
 * @param[out] data error_parse is set to true if an error happens.
 * @param[in, out] last_treated Last treated token type, is updated.
 * @param[in] token Current token to convert.
 * @param[in, out] cmd Current command to which we add args/redirs or create
 * a new command.
 */
void	token_converter(t_data *data, t_node_type *last_treated,
	t_token *token, t_cmd **cmd)
{
	if (*last_treated == TREE_ND && token->type != TREE_CMD)
		parse_error(data, NULL, token);
	else if (*last_treated == TREE_ND && token->type == TREE_CMD)
		token_convert_cmd(token, cmd);
	else if (*last_treated == TREE_PIPE && token->type != TREE_CMD)
		parse_error(data, NULL, token);
	else if (*last_treated == TREE_PIPE && token->type == TREE_CMD)
		token_convert_cmd(token, cmd);
	else if (token->type == TREE_PIPE)
		token_convert_pipe(cmd);
	else if (token->type == TREE_REDIR)
		token_convert_redir(token, cmd);
	else if (*last_treated == TREE_REDIR && token->type == TREE_CMD)
		parse_error(data, NULL, token);
	else if (*last_treated == TREE_CMD && token->type == TREE_CMD)
		token_convert_cmd(token, cmd);
	*last_treated = token->type;
}

/**
 * @brief Convert the token list into a command list.
 * 
 * @param[in, out] data cmd is created and error_parse can be set to true.
 */
void	token_to_cmd(t_data *data)
{
	t_node_type	last_treated;
	t_token		*cur_token;
	t_cmd		*cur_cmd;

	last_treated = TREE_ND;
	cur_token = data->token;
	data->cmd = new_cmd();
	cur_cmd = data->cmd;
	while (cur_token && !data->error_parse)
	{
		token_converter(data, &last_treated, cur_token, &cur_cmd);
		cur_token = cur_token->next;
	}
}
