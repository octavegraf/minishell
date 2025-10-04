/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocgraf <ocgraf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 18:19:31 by ocgraf            #+#    #+#             */
/*   Updated: 2025/10/02 15:28:51 by ocgraf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/exec.h"

void	double_free(void **ptr)
{
	int	i;

	if (!ptr)
		return ;
	i = -1;
	while (ptr && ptr[++i])
		free(ptr[i]);
	free(ptr);
}

void	free_redir(t_redir *redir)
{
	t_redir	*next;

	while (redir)
	{
		next = redir->next;
		if (redir->target)
			free(redir->target);
		free(redir);
		redir = next;
	}
}

void	free_cmd(t_cmd *cmd)
{
	int		i;
	t_cmd	*next;

	while (cmd)
	{
		next = cmd->next;
		i = -1;
		while (cmd->args && cmd->args[++i])
			free(cmd->args[i]);
		if (cmd->args)
			free(cmd->args);
		if (cmd->cmd_path)
			free(cmd->cmd_path);
		if (cmd->redirs)
			free_redir(cmd->redirs);
		free(cmd);
		cmd = next;
	}
}

void	free_token(t_token *token)
{
	t_token	*next;

	while (token)
	{
		next = token->next;
		if (token->inputs)
			free(token->inputs);
		if (token->target)
			free(token->target);
		free(token);
		token = next;
	}
}
