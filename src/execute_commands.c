/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pibouill <pibouill@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 10:43:33 by pibouill          #+#    #+#             */
/*   Updated: 2025/01/14 11:07:11 by pibouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include <signal.h>

void	fork_it(t_cmd *cmd, t_info *info,
	t_exec_info *exe_info, struct sigaction sa)
{
	exe_info->pid = fork();
	(void)sa;
	if (exe_info->pid == -1)
	{
		perror("fork");
		info->exit_code = errno;
		if (exe_info->fd[0] > 0)
			close(exe_info->fd[0]);
		if (exe_info->fd[1] > 1)
			close(exe_info->fd[1]);
		return ;
	}
	if (exe_info->pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		prepare_exe(cmd, info->status, info, exe_info->fd);
		ft_execve(cmd, info, exe_info->pipe_fd);
	}
}

void	do_exe(t_exec_info *exe_info, t_cmd *cmd, t_info *info, struct sigaction
		sa)
{
	exe_info->fd[1] = 1;
	info->i = 0;
	info->status = 0;
	set_redirs(cmd, info, exe_info->fd);
	info->i = exe_pipe(exe_info->pipe_fd, exe_info->fd, cmd);
	if (info->i)
		return ;
	if (is_builtin(cmd) && cmd->next == NULL && cmd->prev == NULL)
	{
		if (info->status != -1)
			info->exit_code = run_builtin(cmd, info, exe_info->fd[1]);
	}
	else
		fork_it(cmd, info, exe_info, sa);
	if (exe_info->fd[0] > 0)
		close(exe_info->fd[0]);
	if (exe_info->fd[1] > 1)
		close(exe_info->fd[1]);
	if (cmd->next)
	{
		close(exe_info->pipe_fd[1]);
		exe_info->fd[0] = exe_info->pipe_fd[0];
	}
	// cmd = cmd->next;
}

void	execute_commands(t_cmd *cmd, t_info *info)
{
	t_exec_info			exe_info;
	struct sigaction	sa;

	exe_info.pid = -1;
	exe_info.fd[0] = 0;
	sa.sa_handler = SIG_DFL;
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	while (cmd != NULL)
	{
		do_exe(&exe_info, cmd, info, sa);
		cmd = cmd->next;
	}
	ft_wait(exe_info.pid, info->status, info);
	setup_signals();
}
