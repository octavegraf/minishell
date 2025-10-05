/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljudd <ljudd@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 11:46:52 by ljudd             #+#    #+#             */
/*   Updated: 2025/10/05 13:46:41 by ljudd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Add a string to the given array of strings. Create a new array and
 * free the input one.
 * @param[in, out] vec Input array.
 * @param[in] str String to add.
 * @return New array created.
 */
char	**add_to_args(char	**vec, char *str, t_data *data)
{
	int		l;
	char	**res;

	l = 0;
	while (vec[l])
		l++;
	res = ft_calloc(l + 2, sizeof(char *));
	if (!res)
		clean_exit(data, 12);
	l = -1;
	while (vec[++l])
	{
		res[l] = ft_strdup(vec[l]);
		if (!res[l])
			clean_exit(data, 12);
		free(vec[l]);
	}
	res[l] = ft_strdup(str);
	if (!res[l])
		clean_exit(data, 12);
	free(vec);
	return (res);
}

/**
 * @brief Indicate that an error happened during the parsing and print an error
 *  message.
 * @param[out] data error_parse is set to true.
 * @param[in] msg Message to be printed.
 * @param[in] token If no message is given, print an error message depending
 * on the token type.
 */
void	parse_error(t_data *data, char *msg, t_token *token)
{
	data->error_parse = true;
	if (msg)
		ft_dprintf(2, "%s", msg);
	else if (token)
	{
		data->error_parse = true;
		if (token->type == TREE_PIPE)
			ft_dprintf(2, "parse error near '|'\n");
		else if (token->type == TREE_CMD)
			ft_dprintf(2, "parse error near cmd\n");
		else if (token->redir_type == REDIR_IN)
			ft_dprintf(2, "parse error near '<'\n");
		else if (token->redir_type == REDIR_OUT)
			ft_dprintf(2, "parse error near '>'\n");
		else if (token->redir_type == REDIR_APPEND)
			ft_dprintf(2, "parse error near '>>'\n");
		else if (token->redir_type == REDIR_HEREDOC)
			ft_dprintf(2, "parse error near '<<'\n");
	}
}

/**
 * @brief Print in output the list of tokens. Used for debugging.
 * @param[in] token First token of the list.
 */
void	token_visualizer(t_token *token)
{
	while (token)
	{
		ft_printf("inputs:%s\n", token->inputs);
		ft_printf("quoted:%c\n", token->quoted);
		ft_printf("type:%d\n", token->type);
		ft_printf("redir_type:%d\n", token->redir_type);
		ft_printf("target:%s\n\n", token->target);
		token = token->next;
	}
}

/**
 * @brief Print in output the list of env variables. Used for debugging.
 * @param[in] env First env variable of the list.
 */
void	env_visualizer(t_env *env)
{
	while (env)
	{
		ft_printf("name:%s\n", env->name);
		ft_printf("value:%s\n\n", env->value);
		env = env->next;
	}
}

/**
 * @brief Print in output the list of commands. Used for debugging.
 * @param[in] cmd First cmd of the list.
 */
void	cmd_visualizer(t_cmd *cmd)
{
	int	l;

	while (cmd)
	{
		ft_printf("COMMAND\n");
		ft_printf("cmd_path:%s\n", cmd->cmd_path);
		ft_printf("args:\n");
		l = -1;
		while (cmd->args[++l])
			ft_printf("%s\n", cmd->args[l]);
		ft_printf("redirs:\n");
		while (cmd->redirs)
		{
			ft_printf("%s\n", cmd->redirs->target);
			cmd->redirs = cmd->redirs->next;
		}
		ft_printf("\n\n");
		cmd = cmd->next;
	}
}
