/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntsvetko <ntsvetko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 17:16:54 by ntsvetko          #+#    #+#             */
/*   Updated: 2024/11/25 17:40:18 by ntsvetko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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

void	exe_output(int *fd_out, char *str, int *exit_code, int *status)
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

void	exe_append(int *fd_out, char *str, int *exit_code, int *status)
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

int	exe_pipe(int pipe_fd[2], int fd[2], t_cmd *cmd)
{
	if (cmd->next)
	{
		if (pipe(pipe_fd) == -1)
		{
			perror("pipe");
			if (fd[0] != 0)
				close(fd[0]);
			if (fd[1] != 1)
				close(fd[1]);
			return (errno);
		}
		if (!cmd->output && !cmd->append)
			fd[1] = pipe_fd[1];
	}
	return (0);
}
