/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_to_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pibouill <pibouill@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 11:15:22 by pibouill          #+#    #+#             */
/*   Updated: 2024/11/24 12:10:09 by pibouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include <dirent.h>
#include <unistd.h>

static char	*get_cmd(t_info *info, char *cmd)
{
	char	*try;
	char	*tmp;
	int		i;

	i = 0;
	while (info->paths[i])
	{
		tmp = ft_strjoin(info->paths[i], "/");
		if (!tmp)
			return (perror("Alloc failed for tmp"), NULL);
		try = ft_strjoin(tmp, cmd);
		if (!try)
			return (perror("Alloc failed for try"), NULL);
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

static void	handle_not_builtin(t_cmd *cmd_lst, t_info *info)
{
	DIR		*dir;
	char	*tmp;

	dir = opendir(cmd_lst->args[0]);
	if (dir != NULL)
	{
		closedir(dir);
		handle_dir_error(cmd_lst, info);
	}
	else if (ft_strchr(cmd_lst->args[0], '/'))
	{
		execve(cmd_lst->args[0], cmd_lst->args, info->my_envp);
		handle_execve_error(cmd_lst, info);
	}
	else if (access(cmd_lst->args[0], X_OK) != 0)
	{
		tmp = cmd_lst->args[0];
		cmd_lst->args[0] = get_cmd(info, tmp);
		free(tmp);
	}
}

void	cmd_to_path(t_cmd *cmd_lst, t_info *info)
{
	while (cmd_lst)
	{
		if (cmd_lst->args[0][0] == '\0' && cmd_lst->args[1])
			del_arg(cmd_lst->args);
		if (cmd_lst->args && cmd_lst->args[0][0] != '\0')
		{
			if (!is_builtin(cmd_lst))
				handle_not_builtin(cmd_lst, info);
		}
		cmd_lst = cmd_lst->next;
	}
}
