/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocgraf <ocgraf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 15:00:00 by ocgraf            #+#    #+#             */
/*   Updated: 2025/09/30 13:12:15 by ocgraf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/exec.h"

static int	g_heredoc_interrupted = 0;
static int	g_signal_received = 0;

void	handle_sigint(int sig)
{
	(void)sig;
	g_signal_received = 1;
	write(STDOUT_FILENO, "\n", 1);
}

int	get_signal_received(void)
{
	return (g_signal_received);
}

void	reset_signal_received(void)
{
	g_signal_received = 0;
}

void	handle_heredoc_sigint(int sig)
{
	(void)sig;
	g_heredoc_interrupted = 1;
	write(STDOUT_FILENO, "\n", 1);
	close(STDIN_FILENO);
}

void	setup_signals(void)
{
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
}

void	setup_heredoc_signals(void)
{
	g_heredoc_interrupted = 0;
	signal(SIGINT, handle_heredoc_sigint);
	signal(SIGQUIT, SIG_IGN);
}

int	is_heredoc_interrupted(void)
{
	return (g_heredoc_interrupted);
}

void	setup_child_signals(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}
