/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pibouill <pibouill@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 13:21:59 by pibouill          #+#    #+#             */
/*   Updated: 2024/11/27 18:33:28 by pibouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

pid_t	setup_child_process(t_cmd *cmd, t_info *info, int *fd)
{
	pid_t	pid;
	int		status = 0;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		info->exit_code = errno;
		return -1;
	}
	signal(SIGINT, SIG_IGN);
	if (pid == 0)
	{
		struct sigaction sa;
		sa.sa_handler = SIG_DFL;
		sa.sa_flags = SA_RESTART;
		sigemptyset(&sa.sa_mask);
		sigaction(SIGINT, &sa, NULL);
		prepare_exe(cmd, status, info, fd);
		ft_execve(cmd, info, NULL);
	}
	return pid;
}

int handle_redirects_and_pipe(t_cmd *cmd, t_info *info, int *fd, int *pipe_fd)
{
	int status;

	status = 0;
	fd[1] = 1;
	set_redirs(cmd, info, &status, fd);
	if (cmd->next)
	{
		if (pipe(pipe_fd) == -1)
		{
			perror("pipe");
			return -1;
		}
		if (!cmd->output && !cmd->append)
			fd[1] = pipe_fd[1];
	}
	return status;
}

int process_command(t_cmd *cmd, t_info *info, int *last_pid, int *fd)
{
	int		pipe_fd[2];
	int		status;
	pid_t	pid;

	status = handle_redirects_and_pipe(cmd, info, fd, pipe_fd);
	if (status == -1)
		return -1;
	if (is_builtin(cmd) && !cmd->next && !cmd->prev)
	{
		if (status != -1)
			info->exit_code = run_builtin(cmd, info, fd[1]);
		return 0;
	}
	pid = setup_child_process(cmd, info, fd);
	if (pid == -1)
		return -1;
	*last_pid = pid;
	return 0;
}

void execute_commands(t_cmd *cmd, t_info *info)
{
	int fd[2];
	pid_t last_pid = -1;
	int result = 0;

	fd[0] = 0;
	fd[1] = 1;
	while (cmd != NULL)
	{
		result = process_command(cmd, info, &last_pid, fd);
		if (result == -1)
			return;
		if (cmd->next)
		{
			close(fd[1]);
			fd[0] = result;
		}
		cmd = cmd->next;
	}
	ft_wait(last_pid, 0, info);
	signal(SIGINT, ft_signal_handler);
}

// void execute_commands(t_cmd *cmd, t_info *info, int status, int i)
// {
//   int pipe_fd[2];
//   pid_t pid;
//   int fd[2];
//
//   pid = -1;
//   fd[0] = 0;
//   while (cmd != NULL)
//   {
//     fd[1] = 1;
//     i = 0;
//     status = 0;
//     set_redirs(cmd, info, &status, fd);
//     i = exe_pipe(pipe_fd, fd, cmd);
//     if (i)
//       return;
//     if (is_builtin(cmd) && cmd->next == NULL && cmd->prev == NULL)
// 	{
//       if (status != -1)
//         info->exit_code = run_builtin(cmd, info, fd[1]);
//     } else
// 	{
//       pid = fork();
//       if (pid == -1)
// 	  {
//         perror("fork");
//         info->exit_code = errno;
//         if (fd[0] != 0)
//           close(fd[0]);
//         if (fd[1] != 1)
//           close(fd[1]);
//         return;
//       }
//       signal(SIGINT, SIG_IGN);
//       if (pid == 0)
// 	  {
//         struct sigaction sa;
//         sa.sa_handler = SIG_DFL;
//         /*sa.sa_handler = sig_handl_child;*/
//         sa.sa_flags = SA_RESTART;
//         sigemptyset(&sa.sa_mask);
//         sigaction(SIGINT, &sa, NULL);
//         // signal(SIGINT, SIG_DFL);
//         prepare_exe(cmd, status, info, fd);
//         ft_execve(cmd, info, pipe_fd);
//       }
//     }
//     if (fd[0] != 0)
//       close(fd[0]);
//     if (fd[1] != 1)
//       close(fd[1]);
//     if (cmd->next)
// 	{
//       close(pipe_fd[1]);
//       fd[0] = pipe_fd[0];
//     }
//     cmd = cmd->next;
//   }
//   ft_wait(pid, status, info);
//   signal(SIGINT, ft_signal_handler);
// }
