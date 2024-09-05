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
			return(try);
		}
		free(try);
		free(tmp);
		paths++;
	}
	printf("cmd \"%s\" doesn\'t exist\n", cmd);
	return (NULL);
}

void cmd_to_path(t_cmd *cmd_lst, t_info info)
{
    char	*tmp;
	while (cmd_lst)
    {
        tmp = cmd_lst->args[0]; 
        cmd_lst->args[0] = get_cmd(info.paths, tmp);
		free(tmp);
        cmd_lst = cmd_lst->next;
    }
}

void execute_commands(t_cmd *cmd, t_token *token, char **envp) {
    int fd_in;
	int fd_out;
    int pipe_fd[2];
	pid_t pid;
	
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
				return;
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

        pid = fork();
        if (pid == -1)
		{
            perror("fork");
            //error
        }

        if (pid == 0)
		{
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

            execve(cmd->args[0], cmd->args, envp);
            perror("execve");
            //error
        }

        if (!cmd->next)
            waitpid(pid, NULL, 0);

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

    while (wait(NULL) > 0);
}