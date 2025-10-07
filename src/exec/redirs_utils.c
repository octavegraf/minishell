/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljudd <ljudd@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 15:30:00 by ljudd             #+#    #+#             */
/*   Updated: 2025/10/06 16:16:49 by ljudd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/exec.h"

int	open_redir_out(t_redir *redir, int append)
{
	if (!redir || !redir->target)
		return (-1);
	if (append)
		return (open(redir->target, O_WRONLY | O_CREAT | O_APPEND, 0644));
	else
		return (open(redir->target, O_WRONLY | O_CREAT | O_TRUNC, 0644));
}

int	open_redir_in(t_redir *redir)
{
	if (!redir || !redir->target)
		return (-1);
	return (open(redir->target, O_RDONLY));
}

int	open_redir_fd(t_redir *redir)
{
	if (redir->type == REDIR_OUT)
		return (open_redir_out(redir, 0));
	else if (redir->type == REDIR_APPEND)
		return (open_redir_out(redir, 1));
	else if (redir->type == REDIR_IN)
		return (open_redir_in(redir));
	else if (redir->type == REDIR_HEREDOC)
		return (dup(redir->heredoc_fd));
	return (-1);
}

int	apply_single_redir(t_redir *redir, int fd)
{
	int	dup_result;

	if (redir->type == REDIR_OUT || redir->type == REDIR_APPEND)
		dup_result = dup2(fd, STDOUT_FILENO);
	else
		dup_result = dup2(fd, STDIN_FILENO);
	if (dup_result < 0)
		return (close(fd), perror("dup2"), 1);
	return (0);
}
