/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_not_builtin.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pibouill <pibouill@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 08:23:37 by pibouill          #+#    #+#             */
/*   Updated: 2025/01/15 08:27:43 by pibouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>

static void	handle_dir_error(t_cmd *cmd_lst, t_info *info)
{
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

static void	handle_execve_error(t_cmd *cmd_lst, t_info *info)
{
	perror(cmd_lst->args[0]);
	free(cmd_lst->args[0]);
	if (errno == EACCES)
		info->exit_code = 126;
	else
		info->exit_code = 127;
	cmd_lst->args[0] = ft_strdup("");
}

static void	handle_file_with_path(t_cmd *cmd_lst, t_info *info,
	struct stat *statbuf)
{
	if (S_ISDIR(statbuf->st_mode))
		handle_dir_error(cmd_lst, info);
	else if (S_ISREG(statbuf->st_mode))
	{
		if (statbuf->st_mode & S_IXUSR)
		{
			execve(cmd_lst->args[0], cmd_lst->args, info->my_envp);
			handle_execve_error(cmd_lst, info);
		}
		else
		{
			errno = EACCES;
			handle_execve_error(cmd_lst, info);
		}
	}
	else
	{
		errno = EACCES;
		handle_execve_error(cmd_lst, info);
	}
}

void	handle_not_builtin(t_cmd *cmd_lst, t_info *info)
{
	struct stat	statbuf;
	char		*tmp;

	if (ft_strchr(cmd_lst->args[0], '/'))
	{
		if (stat(cmd_lst->args[0], &statbuf) == 0)
			handle_file_with_path(cmd_lst, info, &statbuf);
		else
			handle_execve_error(cmd_lst, info);
	}
	else
	{
		tmp = cmd_lst->args[0];
		cmd_lst->args[0] = get_cmd(info, tmp);
		free(tmp);
	}
}

// static void	handle_not_builtin(t_cmd *cmd_lst, t_info *info)
// {
// 	DIR		*dir;
// 	char	*tmp;
//
// 	dir = opendir(cmd_lst->args[0]);
// 	if (dir != NULL)
// 	{
// 		closedir(dir);
// 		handle_dir_error(cmd_lst, info);
// 	}
// 	else if (ft_strchr(cmd_lst->args[0], '/'))
// 	{
// 		execve(cmd_lst->args[0], cmd_lst->args, info->my_envp);
// 		handle_execve_error(cmd_lst, info);
// 	}
// 	else if (access(cmd_lst->args[0], X_OK) != 0)
// 	{
// 		tmp = cmd_lst->args[0];
// 		cmd_lst->args[0] = get_cmd(info, tmp);
// 		free(tmp);
// 	}
// }
