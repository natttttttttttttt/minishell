/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exe_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pibouill <pibouill@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 13:40:00 by pibouill          #+#    #+#             */
/*   Updated: 2025/01/14 13:40:17 by pibouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_wait(pid_t pid, int status, t_info *info)
{
	if (pid != -1)
	{
		waitpid(pid, &status, 0);
		if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
			write(1, "\n", 1);
		if (WIFEXITED(status))
			info->exit_code = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			info->exit_code = 128 + WTERMSIG(status);
	}
	while (wait(NULL) > 0)
		;
}

void	setup_child_signals(struct sigaction *sa)
{
	sa->sa_handler = SIG_DFL;
	sa->sa_flags = SA_RESTART;
	sigemptyset(&sa->sa_mask);
	sigaction(SIGINT, sa, NULL);
}
