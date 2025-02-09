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

void ft_signal_handler(int signal)
{
    g_sigflag = signal;
    if (signal == SIGINT)
    {
        write(1, "\n", 1);
        rl_replace_line("", 0);
        rl_on_new_line();
        rl_redisplay();
    }
}

void setup_signals(void)
{
    struct sigaction sa;

    // sa.sa_handler = sigquit_handler;
    sa.sa_flags = 0;
    sigemptyset(&sa.sa_mask);
	sa.sa_handler = ft_signal_handler;
	if (sigaction(SIGINT, &sa, NULL) == -1)
	{
		perror("error setting sigquit_handler");
		exit(EXIT_FAILURE);
	}
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
}
