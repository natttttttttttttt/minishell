#include "minishell.h"

static char	*get_cmd(char **paths, char *cmd)
{
	char	*try;
	char	*tmp;

	while (*paths)
	{
		tmp = ft_strjoin(*paths, "/");
		try = ft_strjoin(tmp, cmd);
		if (access(try, X_OK) == 0)
		{
			free(tmp);
			return (try);
		}
		free(try);
		free(tmp);
		paths++;
	}
	printf("%s: command not found\n", cmd);
	return (ft_strdup(""));
}


void	cmd_to_path(t_cmd *cmd_lst, t_info info)
{
	char	*tmp;

	while (cmd_lst)
	{
		if (!is_builtin(cmd_lst))
		{
			if (access(cmd_lst->args[0], X_OK) != 0)
			{
				tmp = cmd_lst->args[0];
				cmd_lst->args[0] = get_cmd(info.paths, tmp);
				free(tmp);
			}
		}
		cmd_lst = cmd_lst->next;
	}
}

void	run_builtin(t_cmd *cmd, t_info *info)
{
	if (is_builtin(cmd) == BUILTIN_PWD)
		pwd_builtin();
	else if (is_builtin(cmd) == BUILTIN_CD)
		cd_builtin(cmd->args, info);
	else if (is_builtin(cmd) == BUILTIN_EXIT)
		exit_builtin(cmd->args);
	else if (is_builtin(cmd) == BUILTIN_ENV)
		builtin_env(info->my_envp);
	else if (is_builtin(cmd) == BUILTIN_EXPORT)
		export_builtin(cmd->args, info);
	else if (is_builtin(cmd) == BUILTIN_UNSET)
		unset_builtin(cmd->args, info, 1, 0);
	else if (is_builtin(cmd) == BUILTIN_ECHO)
		echo_builtin(cmd->args);
}

void	execute_commands(t_cmd *cmd, t_info *info)
{
	int		fd_in;
	int		fd_out;
	int		pipe_fd[2];
	pid_t	pid;

	fd_in = 0;
	while (cmd != NULL)
	{
		fd_out = 1;
		if (cmd->input)
		{
			fd_in = open(cmd->input, O_RDONLY);
			if (fd_in == -1)
			{
				perror("input");
				return ;
			}
		}
		if (cmd->output)
		{
			fd_out = open(cmd->output, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (fd_out == -1)
			{
				perror("output");
				//error
			}
		}
		else if (cmd->append)
		{
			fd_out = open(cmd->append, O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (fd_out == -1)
			{
				perror("append");
				//error
			}
		}
		if (cmd->next)
		{
			if (pipe(pipe_fd) == -1)
			{
				perror("pipe");
				//error
			}
			if (!cmd->output)
				fd_out = pipe_fd[1];
		}
		if (cmd->builtin && cmd->next == NULL && cmd->prev == NULL)
			run_builtin(cmd, info);
		else
		{
			pid = fork();
			if (pid == -1)
			{
				perror("fork");
				//error
			}
			if (pid == 0)
			{
				if (cmd->args[0] == NULL)
					exit (1);
				if (fd_in != 0)
				{
					if (dup2(fd_in, 0) == -1)
					{
						perror("dup2");
						//error
					}
					close(fd_in);
				}
				if (fd_out != 1)
				{
					if (dup2(fd_out, 1) == -1)
					{
						perror("dup2");
						//error
					}
					close(fd_out);
				}
				if (cmd->next)
					close(pipe_fd[0]);
				if (cmd->builtin)
				{
					run_builtin(cmd, info);
					//close(fd_out);
					exit (0);
				}
				else
				{
					execve(cmd->args[0], cmd->args, info->my_envp);
					perror("execve");
					//error
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
	while (wait(NULL) > 0)
		;
}
