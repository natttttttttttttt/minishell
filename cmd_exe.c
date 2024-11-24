#include "minishell.h"
#include <endian.h>
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

void	exe_input(int *fd_in, char *str, int *exit_code, int *status)
{
	if (*status != -1)
	{
		*fd_in = open(str, O_RDONLY);
		if (*fd_in == -1)
		{
			perror(str);
			*exit_code = 1;
			*status = -1;
		}
	}

}
void	exe_heredoc(char **str, t_info *info, int *fd_in, int *status)
{
	if (*status != -1)
	{
		heredoc(str, *info);
		*fd_in = open("heredoc.tmp", O_RDONLY);
		unlink("heredoc.tmp");
		if (*fd_in == -1)
		{
			perror("heredoc.tmp");
			*fd_in = 0;
			info->exit_code = 1;
			*status = -1;
		}
	}
}


void exe_output(int *fd_out, char *str, int *exit_code, int *status)
{
	if (*status != -1)
	{
		*fd_out = open(str, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (*fd_out == -1)
		{
			perror(str);
			*exit_code = 1;
			*status = -1;
		}
	}
}

void exe_append(int *fd_out, char *str, int *exit_code, int *status)
{
	if (*status != -1)
	{
		*fd_out = open(str, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (*fd_out == -1)
		{
			perror(str);
			*exit_code = 1;
			*status = -1;
		}
	}
}

int	exe_pipe(int pipe_fd[2], int fd_in, int *fd_out, t_cmd *cmd)
{
	if (cmd->next)
	{
		if (pipe(pipe_fd) == -1)
		{
			perror("pipe");
			if (fd_in != 0)
				close(fd_in);
			if (*fd_out != 1)
				close(*fd_out);
			return (errno);
		}
		if (!cmd->output && !cmd->append)
			*fd_out = pipe_fd[1];
	}
	return (0);
}

void	execute_commands(t_cmd *cmd, t_info *info, int fd_in, int fd_out)
{
	int		pipe_fd[2];
	pid_t	pid;
	int		status;
	int		pipe_failed;
	int i;

	pid = -1;
	
	while (cmd != NULL)
	{
		fd_out = 1;
		i = 0;
		status = 0;
		while(i < cmd->order->count)
		{
			if (cmd->input && (i + '0' == cmd->order->input[cmd->order->i_input]))
			{
				exe_input(&fd_in, cmd->input[cmd->order->i_input], &(info->exit_code), &status);
				cmd->order->i_input++;
			}
			else if (cmd->output && (i + '0' == cmd->order->output[cmd->order->i_output]))
			{
				exe_output(&fd_out, cmd->output[cmd->order->i_output], &(info->exit_code), &status);
				cmd->order->i_output++;
			}
			else if (cmd->append && (i + '0' == cmd->order->append[cmd->order->i_append]))
			{
				exe_append(&fd_out, cmd->append[cmd->order->i_append], &(info->exit_code), &status);
				cmd->order->i_append++;
			}
			else if (cmd->delimiter && (i + '0' == cmd->order->heredoc[0]))
				exe_heredoc(cmd->delimiter, info, &fd_in, &status);
			i++;
		}
		pipe_failed = exe_pipe(pipe_fd, fd_in, &fd_out, cmd);
		if (pipe_failed)
			return ;
		if (is_builtin(cmd) && cmd->next == NULL && cmd->prev == NULL)
		{
			if (status != -1)
				info->exit_code = run_builtin(cmd, info, fd_out);
		}
		else
		{
			pid = fork();
			if (pid == -1)
			{
				perror("fork");
				info->exit_code = errno;
				if (fd_in != 0)
					close(fd_in);
				if (fd_out != 1)
					close(fd_out);
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
				if (!cmd->args || cmd->args[0][0] == '\0' || status == -1)
				{	
					free_before_exit(info);
					exit(info->exit_code);
				}
				if (fd_in != 0)
				{
					if (dup2(fd_in, 0) == -1)
					{
						perror("dup2");
						free_before_exit(info);
						exit(errno);
					}
				}
				if (fd_out != 1)
				{
					if (dup2(fd_out, 1) == -1)
					{
						perror("dup2");
						free_before_exit(info);
						exit (errno);
					}
				}
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
		}
		if (fd_in != 0)
			close(fd_in);
		if (fd_out != 1)
			close(fd_out);
		if (cmd->next)
		{
			close(pipe_fd[1]);
			fd_in = pipe_fd[0];
		}
		cmd = cmd->next;
	}
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
	signal(SIGINT, ft_signal_handler);
}

//test 136
