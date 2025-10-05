/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljudd <ljudd@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 11:28:18 by ocgraf            #+#    #+#             */
/*   Updated: 2025/10/05 18:26:52 by ljudd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/exec.h"

extern int	g_signal;

void	set_heredoc_interrupted(int value)
{
	if (value)
		g_signal = SIGINT;
	else
		g_signal = 0;
}

int	get_heredoc_interrupted(void)
{
	return (g_signal == SIGINT);
}

void	handle_heredoc_sigint(int sig)
{
	g_signal = sig;
	write(STDOUT_FILENO, "\n", 1);
	close(STDIN_FILENO);
}

void	setup_heredoc_signals(void)
{
	g_signal = 0;
	signal(SIGINT, handle_heredoc_sigint);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
}
