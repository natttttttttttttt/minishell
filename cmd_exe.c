#include "minishell.h"
#include <endian.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
//can norminette cmd_to_path
static char	*get_cmd(t_info *info, char *cmd)
{
	char	*try;
	char	*tmp;
	int		i;

	i = 0;
	while (info->paths[i])
	{
		tmp = ft_strjoin(info->paths[i], "/");
		try = ft_strjoin(tmp, cmd);
		if (access(try, X_OK) == 0)
		{
			free(tmp);
			return (try);
		}
		free(try);
		free(tmp);
		i++;
	}
	printf("%s: command not found\n", cmd);
	info->exit_code = 127;
	return (ft_strdup(""));
}

void	sig_handl_child(int signal);

void	cmd_to_path(t_cmd *cmd_lst, t_info *info)
{
	char	*tmp;
	DIR		*dir;

	while (cmd_lst)
	{
		if (cmd_lst->args[0][0] == '\0' && cmd_lst->args[1])
			del_arg(cmd_lst->args);
		if (cmd_lst->args && cmd_lst->args[0][0] != '\0')
		{
			if (!is_builtin(cmd_lst))
			{
				dir = opendir(cmd_lst->args[0]);
				if ((ft_strchr(cmd_lst->args[0], '/'))  && (errno == ENOENT || errno == EACCES))
				{
					if (errno == ENOENT)
						info->exit_code = 127;
					else
						info->exit_code = 126;
					perror(cmd_lst->args[0]);
					free(cmd_lst->args[0]);
					cmd_lst->args[0] = ft_strdup("");
				}
				else if (dir != NULL)
				{
					closedir(dir);
					if (ft_strncmp(cmd_lst->args[0], "./", 2) == 0
						|| ft_strncmp(cmd_lst->args[0], "../", 3) == 0
						|| ft_strncmp(cmd_lst->args[0], "/", 1) == 0)
					{
						printf("%s: is a directory\n", cmd_lst->args[0]);
						info->exit_code = 126;
					}
					else
					{
						printf("%s: command not found\n", cmd_lst->args[0]);
						info->exit_code = 127;
					}
					free(cmd_lst->args[0]);
					cmd_lst->args[0] = ft_strdup("");
				}
				// else if (ft_strchr(cmd_lst->args[0], '/'))
				// {
				// 	execve(cmd_lst->args[0], cmd_lst->args, info->my_envp);
				// 	perror(cmd_lst->args[0]);
				// 	free(cmd_lst->args[0]);
				// 	if (errno == 13)
				// 		info->exit_code = 126;
				// 	else
				// 		info->exit_code = 127;
				// 	cmd_lst->args[0] = ft_strdup("");
				// }
				else if ((access(cmd_lst->args[0], F_OK) == 0) && !(ft_strchr(cmd_lst->args[0], '/')))
				{
					printf("%s: command not found\n", cmd_lst->args[0]);
					info->exit_code = 127;
					free(cmd_lst->args[0]);
					cmd_lst->args[0] = ft_strdup("");
				}
				else if (access(cmd_lst->args[0], X_OK) != 0)
				{
					tmp = cmd_lst->args[0];
					cmd_lst->args[0] = get_cmd(info, tmp);
					free(tmp);
				}
			}
		}
		cmd_lst = cmd_lst->next;
	}
}

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

void	exe_input(int *fd_in, t_cmd *cmd, int *exit_code, int *status)
{
	int	i;

	i = 0;
	while (cmd->input[i])
	{
		*fd_in = open(cmd->input[i], O_RDONLY);
		if (*fd_in == -1)
		{
			perror(cmd->input[i]);
			*exit_code = 1;
			*status = -1;
			break ;
		}
		i++;
	}
}
void	exe_heredoc(t_cmd *cmd, t_info *info, int *fd_in, int *status)
{
	heredoc(cmd->delimiter, *info);
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

void	execute_commands(t_cmd *cmd, t_info *info)
{
	int		fd_in;
	int		fd_out;
	int		pipe_fd[2];
	pid_t	pid;
	int		status;
	int i;

	fd_in = 0;
	while (cmd != NULL)
	{
		fd_out = 1;
		status = 0;
		if (cmd->input)
			exe_input(&fd_in, cmd, &(info->exit_code), &status);
		if (cmd->delimiter)
			exe_heredoc(cmd, info, &fd_in, &status);
		if (cmd->output && status != -1)
		{
			i = 0;
			while (cmd->output[i] != NULL)
			{
				fd_out = open(cmd->output[i], O_WRONLY | O_CREAT | O_TRUNC, 0644);
				if (fd_out == -1)
				{
					perror(cmd->output[i]);
					info->exit_code = 1;
					status = -1;
					break ;
				}
				i++;
			}
		}
		if (cmd->append && status != -1)
		{
			i = 0;
			while ((cmd->append)[i] != NULL)
			{
				fd_out = open(cmd->append[i], O_WRONLY | O_CREAT | O_APPEND, 0644);
				if (fd_out == -1)
				{
					perror(cmd->append[i]);
					info->exit_code = 1;
					status = -1;
					break ;
				}
				i++;
			}
		}
		if (cmd->next)
		{
			if (pipe(pipe_fd) == -1)
			{
				perror("pipe");
				info->exit_code = errno;
				if (fd_in != 0)
					close(fd_in);
				if (fd_out != 1)
					close(fd_out);
				return ;
			}
			if (!cmd->output && !cmd->append)
				fd_out = pipe_fd[1];
		}
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
				if (!cmd->args || cmd->args[0][0] == '\0')
					exit (info->exit_code);
				if (status == -1)
					exit(info->exit_code);
				if (fd_in != 0)
				{
					if (dup2(fd_in, 0) == -1)
					{
						perror("dup2");
						exit (errno);
					}
				}
				if (fd_out != 1)
				{
					if (dup2(fd_out, 1) == -1)
					{
						perror("dup2");
						exit (errno);
					}
				}
				if (cmd->next)
					close(pipe_fd[0]);
				if (is_builtin(cmd))
				{
					info->exit_code = run_builtin(cmd, info, 1);
					exit(info->exit_code);
				}
				else
				{
					execve(cmd->args[0], cmd->args, info->my_envp);
					perror("execve");
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
