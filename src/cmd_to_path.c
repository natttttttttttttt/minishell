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

void	do_close_dir(DIR *dir, t_cmd *cmd_lst, t_info *info)
{
	closedir(dir);
	if (ft_strchr(cmd_lst->args[0], '/'))
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

static void	cmd_not_found(t_cmd *cmd_lst, t_info *info)
{
	printf("%s: command not found\n", cmd_lst->args[0]);
	info->exit_code = 127;
	free(cmd_lst->args[0]);
	cmd_lst->args[0] = ft_strdup("");
}

static void	not_possible(t_info *info, t_cmd *cmd_lst)
{
	if (errno == ENOENT)
		info->exit_code = 127;
	else
		info->exit_code = 126;
	perror(cmd_lst->args[0]);
	free(cmd_lst->args[0]);
	cmd_lst->args[0] = ft_strdup("");
}

static void	possible(t_cmd *cmd_lst, t_info *info)
{
	char	*tmp;

	tmp = NULL;
	tmp = cmd_lst->args[0];
	cmd_lst->args[0] = get_cmd(info, tmp);
	free(tmp);
}

void	cmd_to_path(t_cmd *cmd_lst, t_info *info)
{
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
				if ((ft_strchr(cmd_lst->args[0], '/'))
					&& (errno == ENOENT || errno == EACCES))
					not_possible(info, cmd_lst);
				else if (dir != NULL)
					do_close_dir(dir, cmd_lst, info);
				else if ((access(cmd_lst->args[0], F_OK) == 0)
					&& !(ft_strchr(cmd_lst->args[0], '/')))
					cmd_not_found(cmd_lst, info);
				else if (access(cmd_lst->args[0], X_OK) != 0)
					possible(cmd_lst, info);
			}
		}
		cmd_lst = cmd_lst->next;
	}
}
