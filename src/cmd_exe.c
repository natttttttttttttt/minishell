/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pibouill <pibouill@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 13:38:36 by pibouill          #+#    #+#             */
/*   Updated: 2024/12/06 13:39:12 by pibouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
// #include <endian.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
//can norminette cmd_to_path

void	sig_handl_child(int signal);

int	run_builtin(t_cmd *cmd, t_info *info, int fd_out)
{
	if (is_builtin(cmd) == BUILTIN_PWD)
		return (pwd_builtin());
	else if (is_builtin(cmd) == BUILTIN_CD)
		return (cd_builtin(cmd->args, info));
	else if (is_builtin(cmd) == BUILTIN_EXIT)
		exit_builtin(cmd->args, info);
	else if (is_builtin(cmd) == BUILTIN_ENV)
		return (env_builtin(info->my_envp, fd_out), fd_out);
	else if (is_builtin(cmd) == BUILTIN_EXPORT)
		return (export_builtin(cmd->args, info, 1));
	else if (is_builtin(cmd) == BUILTIN_UNSET)
		return (unset_builtin(cmd->args, info, 1, 0));
	else if (is_builtin(cmd) == BUILTIN_ECHO)
		return (echo_builtin(cmd->args, fd_out));
	return (0);
}

void	ft_execve(t_cmd *cmd, t_info *info, int pipe_fd[2])
{
	if (cmd->next)
		close(pipe_fd[0]);
	if (is_builtin(cmd))
	{
		info->exit_code = run_builtin(cmd, info, 1);
		free_before_exit(info);
		exit(info->exit_code);
	}
	else
	{
		execve(cmd->args[0], cmd->args, info->my_envp);
		perror("execve");
		free_before_exit(info);
		exit(errno);
	}
}

void	prepare_exe(t_cmd *cmd, int status, t_info *info, int fd[2])
{
	if (!cmd->args || cmd->args[0][0] == '\0' || status == -1)
	{
		free_before_exit(info);
		exit(info->exit_code);
	}
	if (fd[0] != 0)
	{
		if (dup2(fd[0], 0) == -1)
		{
			perror("dup2");
			free_before_exit(info);
			exit(errno);
		}
	}
	if (fd[1] != 1)
	{
		if (dup2(fd[1], 1) == -1)
		{
			perror("dup2");
			free_before_exit(info);
			exit (errno);
		}
	}
}

void	set_redirs(t_cmd *cmd, t_info *info, int *status, int fd[2])
{
	int	i;

	i = 0;
	while (i < cmd->order->count)
	{
		if (cmd->input && (i + '0' == cmd->order->input[cmd->order->i_input]))
			exe_input(&fd[0], cmd->input[cmd->order->i_input++],
				&(info->exit_code), status);
		else if (cmd->output && (i + '0'
				== cmd->order->output[cmd->order->i_output]))
			exe_output(&fd[1], cmd->output[cmd->order->i_output++],
				&(info->exit_code), status);
		else if (cmd->append && (i + '0'
				== cmd->order->append[cmd->order->i_append]))
			exe_append(&fd[1], cmd->append[cmd->order->i_append++],
				&(info->exit_code), status);
		else if (cmd->delimiter && (i + '0' == cmd->order->heredoc[0]))
			exe_heredoc(cmd->delimiter, info, &fd[0], status);
		i++;
	}
}

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

// pierre do
void	execute_commands(t_cmd *cmd, t_info *info, int status, int i)
{
	int		pipe_fd[2];
	pid_t	pid;
	int		fd[2];

	pid = -1;
	fd[0] = 0;
	while (cmd != NULL)
	{
		fd[1] = 1;
		i = 0;
		status = 0;
		set_redirs(cmd, info, &status, fd);
		i = exe_pipe(pipe_fd, fd, cmd);
		if (i)
			return ;
		if (is_builtin(cmd) && cmd->next == NULL && cmd->prev == NULL)
		{
			if (status != -1)
				info->exit_code = run_builtin(cmd, info, fd[1]);
		}
		else
		{
			pid = fork();
			if (pid == -1)
			{
				perror("fork");
				info->exit_code = errno;
				if (fd[0] != 0)
					close(fd[0]);
				if (fd[1] != 1)
					close(fd[1]);
				return ;
			}
			signal(SIGINT, SIG_IGN);
			if (pid == 0)
			{
				struct sigaction	sa;
				sa.sa_handler = SIG_DFL;
				/*sa.sa_handler = sig_handl_child;*/
				sa.sa_flags = SA_RESTART;
				sigemptyset(&sa.sa_mask);
				sigaction(SIGINT, &sa, NULL);
				//signal(SIGINT, SIG_DFL);
				prepare_exe(cmd, status, info, fd);
				ft_execve(cmd, info, pipe_fd);
			}
		}
		if (fd[0] != 0)
			close(fd[0]);
		if (fd[1] != 1)
			close(fd[1]);
		if (cmd->next)
		{
			close(pipe_fd[1]);
			fd[0] = pipe_fd[0];
		}
		cmd = cmd->next;
	}
	ft_wait(pid, status, info);
	signal(SIGINT, ft_signal_handler);
}

//test 136
