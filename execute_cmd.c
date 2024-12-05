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

#include "minishell.h"
#include <unistd.h>

void	close_fds(int *fd, int *pipe_fd, t_cmd *cmd)
{
	if (fd[0] != 0)
		close(fd[0]);
	if (fd[1] != 1)
		close(fd[1]);
	if (cmd->next)
		close(pipe_fd[1]);
}

void	execute_child(t_cmd *cmd, t_info *info, int *fd, int *pipe_fd)
{
	struct sigaction	sa;

	sa.sa_handler = SIG_DFL;
	sa.sa_flags = SA_RESTART;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGINT, &sa, NULL);
	prepare_exe(cmd, 0, info, fd);
	ft_execve(cmd, info, pipe_fd);
}

pid_t	create_child(t_cmd *cmd, t_info *info, int *fd, int *pipe_fd)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		info->exit_code = errno;
		close_fds(fd, pipe_fd, cmd);
		return (-1);
	}
	if (pid == 0)
		execute_child(cmd, info, fd, pipe_fd);
	return (pid);
}

int	handle_builtin(t_cmd *cmd, t_info *info, int status, int *fd)
{
	if (is_builtin(cmd) && cmd->next == NULL && cmd->prev == NULL)
	{
		if (status != -1)
			info->exit_code = run_builtin(cmd, info, fd[1]);
		return (1);
	}
	return (0);
}

void	execute_commands(t_cmd *cmd, t_info *info, int status, int i)
{
	int		pipe_fd[2];
	int		fd[2];
	pid_t	pid;

	fd[0] = 0;
	(void)i;
	while (cmd != NULL)
	{
		fd[1] = 1;
		status = 0;
		set_redirs(cmd, info, &status, fd);
		if (is_builtin(cmd) && cmd->next == NULL && cmd->prev == NULL)
		{
			if (status != -1)
				info->exit_code = run_builtin(cmd, info, fd[1]);
			return ;
		}
		if (handle_builtin(cmd, info, status, fd))
			return ;
		pid = create_child(cmd, info, fd, pipe_fd);
		close_fds(fd, pipe_fd, cmd);
		cmd = cmd->next;
	}
	ft_wait(pid, status, info);
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
//   while (cmd != NULL) {
//     fd[1] = 1;
//     i = 0;
//     status = 0;
//     set_redirs(cmd, info, &status, fd);
//     i = exe_pipe(pipe_fd, fd, cmd);
//     if (i)
//       return;
//     if (is_builtin(cmd) && cmd->next == NULL && cmd->prev == NULL) {
//       if (status != -1)
//         info->exit_code = run_builtin(cmd, info, fd[1]);
//     } else {
//       pid = fork();
//       if (pid == -1) {
//         perror("fork");
//         info->exit_code = errno;
//         if (fd[0] != 0)
//           close(fd[0]);
//         if (fd[1] != 1)
//           close(fd[1]);
//         return;
//       }
//       signal(SIGINT, SIG_IGN);
//       if (pid == 0) {
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
//     if (cmd->next) {
//       close(pipe_fd[1]);
//       fd[0] = pipe_fd[0];
//     }
//     cmd = cmd->next;
//   }
//   ft_wait(pid, status, info);
//   signal(SIGINT, ft_signal_handler);
// }
