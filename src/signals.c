/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pibouill <pibouill@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 14:23:31 by pibouill          #+#    #+#             */
/*   Updated: 2024/12/24 12:14:18 by pibouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

extern int	g_sigflag;

void	setup_signals(void)
{
	struct sigaction	sa;

	sa.sa_handler = ft_signal_handler;
	sa.sa_flags = SA_RESTART;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGINT, &sa, NULL);
	signal(SIGINT, ft_signal_handler);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
}

void	sig_handl_child(int signal)
{
	if (signal == SIGINT)
		exit(130);
}

void	ft_signal_handler(int signal)
{
	g_sigflag = signal;
	if (signal == SIGINT)
	{
		//sig_handl_child(signal);
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}
