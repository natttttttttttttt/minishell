/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pibouill <pibouill@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 15:21:33 by pibouill          #+#    #+#             */
/*   Updated: 2024/11/17 15:41:01 by pibouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include <readline/readline.h>
#include <signal.h>
#include <stdio.h>

//void	sigquit_handler(int sig)
//{
//    (void)sig;
//    // check for waiting child before
//    // if so, exit status 131 
//    // and print "Quit (core dumped)
	
//    rl_on_new_line();
//    rl_redisplay();
//}

//void	sigint_handler(int sig)
//{
//    (void)sig;
//    // check for heredoc
//    // -> ioctl(STDIN_FILENO, TIOCSTI, "\n"); -> maybe
//    write(2, "\n", 1);
//    rl_replace_line("", 0);
//    rl_on_new_line();
//    rl_redisplay();
//    // check waiting child
//    // and switch status code to 130 here
//}

//void	setup_signals(void)
//{
//    struct sigaction	sa;

//    sa.sa_handler = sigquit_handler;
//    sa.sa_flags = 0;
//    sigemptyset(&sa.sa_mask);
//    if (sigaction(SIGQUIT, &sa, NULL) == -1)
//    {
//        perror("Cannot set SIGQUIT handler");
//        exit(EXIT_FAILURE);
//    }
//    sa.sa_handler = sigint_handler;
//    sa.sa_flags = SA_SIGINFO | SA_RESTART;
//    sigemptyset(&sa.sa_mask);
//    if (sigaction(SIGINT, &sa, NULL) == -1)
//    {
//        perror("Cannot set SIGINT handler");
//        exit(EXIT_FAILURE);
//    }
//}

void	setup_signals(void)
{
	struct sigaction	sa;

	sa.sa_handler = ft_signal_handler;
	sa.sa_flags = SA_RESTART;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGINT, &sa, NULL);
}

void	sig_handl_child(int signal)
{
	if (signal == SIGINT)
	{
		exit(130);
	}
}

void	ft_signal_handler(int signal)
{
	if (signal == SIGINT)
	{
		//sig_handl_child(signal);
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}
