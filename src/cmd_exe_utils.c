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
		if (WIFSIGNALED(status))
		{
			if (WTERMSIG(status) == SIGINT)
				write(1, "\n", 1);
			else if (WTERMSIG(status) == SIGQUIT)
				write(2, "Quit (core dumped)\n", 19);
			info->exit_code = 128 + WTERMSIG(status);
		}
		else if (WIFEXITED(status))
			info->exit_code = WEXITSTATUS(status);
	}
	while (wait(NULL) > 0)
		;
}
