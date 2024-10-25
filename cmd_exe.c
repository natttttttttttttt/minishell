#include "minishell.h"

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
	return (ft_strdup(""));
}


void	cmd_to_path(t_cmd *cmd_lst, t_info *info)
{
	char	*tmp;

	while (cmd_lst)
	{
		if (cmd_lst->args[0][0] == '\0' && cmd_lst->args[1])
		{
			del_arg(cmd_lst->args);
			print_cmd_lst(cmd_lst);
		}
		if (cmd_lst->args && cmd_lst->args[0][0] != '\0')
		{
			if (!is_builtin(cmd_lst))
			{
				if (ft_strchr(cmd_lst->args[0], '/'))
				{
					if (chdir(cmd_lst->args[0]) == 0)
					{
						printf("%s: is a directory\n", cmd_lst->args[0]);
						free(cmd_lst->args[0]);
						cmd_lst->args[0] = ft_strdup("");
					}
					else
					{
						chdir(cmd_lst->args[0]);
						perror(cmd_lst->args[0]);
						free(cmd_lst->args[0]);
						cmd_lst->args[0] = ft_strdup("");
					}
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
		return (env_builtin(info->my_envp));
	else if (is_builtin(cmd) == BUILTIN_EXPORT)
		return (export_builtin(cmd->args, info, 1));
	else if (is_builtin(cmd) == BUILTIN_UNSET)
		return (unset_builtin(cmd->args, info, 1, 0));
	else if (is_builtin(cmd) == BUILTIN_ECHO)
		return (echo_builtin(cmd->args, fd_out));
	return (0);
}

void	execute_commands(t_cmd *cmd, t_info *info)
{
	int		fd_in;
	int		fd_out;
	int		pipe_fd[2];
	pid_t	pid;
	int		status;

	fd_in = 0;
	pid = -1;
	while (cmd != NULL)
	{
		fd_out = 1;
		status = 0;
		if (cmd->input)
		{
			fd_in = open(cmd->input, O_RDONLY);
			if (fd_in == -1)
			{
				perror(cmd->input);
				fd_in = 0;
				info->exit_code = 1;
				status = -1;
			}
		}
		if (cmd->delimiter)
		{
			heredoc(cmd->delimiter, *info);
			fd_in = open("heredoc.tmp", O_RDONLY);
			unlink("heredoc.tmp");
			if (fd_in == -1)
			{
				perror("heredoc.tmp");
				fd_in = 0;
				info->exit_code = 2;
				cmd = cmd->next;
				continue ;
			}
		}
		if (cmd->output)
		{
			fd_out = open(cmd->output, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (fd_out == -1)
			{
				perror(cmd->output);
				info->exit_code = errno;
				cmd = cmd->next;
				continue ;
			}
		}
		else if (cmd->append)
		{
			fd_out = open(cmd->append, O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (fd_out == -1)
			{
				perror(cmd->append);
				info->exit_code = errno;
				cmd = cmd->next;
				continue ;
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
			fd_out = pipe_fd[1];
		}
		if (is_builtin(cmd) && cmd->next == NULL && cmd->prev == NULL)
			info->exit_code = run_builtin(cmd, info, fd_out);
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
			if (pid == 0)
			{
				if (!cmd->args || cmd->args[0][0] == '\0')
					exit (127);
				if (status == -1)
					exit(0);
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
					exit (info->exit_code);
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
		if (WIFEXITED(status))
			info->exit_code = WEXITSTATUS(status);
	}
	while (wait(NULL) > 0)
		;
}
