/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_to_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pibouill <pibouill@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 11:15:22 by pibouill          #+#    #+#             */
/*   Updated: 2025/02/05 15:46:27 by pibouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include <dirent.h>
#include <unistd.h>

static void	do_close_dir(DIR *dir, t_cmd *cmd_lst, t_info *info)
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

static void	handle_directory_case(DIR *dir, t_cmd *cmd_lst, t_info *info)
{
	if (dir != NULL)
		do_close_dir(dir, cmd_lst, info);
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

static void	process_command(t_cmd *cmd_lst, t_info *info)
{
	DIR	*dir;

	if (!is_builtin(cmd_lst))
	{
		dir = opendir(cmd_lst->args[0]);
		if ((ft_strchr(cmd_lst->args[0], '/'))
			&& (errno == ENOENT || errno == EACCES))
			not_possible(info, cmd_lst);
		else
		{
			handle_directory_case(dir, cmd_lst, info);
			handle_path_checks(cmd_lst, info);
		}
	}
}

void	cmd_to_path(t_cmd *cmd_lst, t_info *info)
{
	while (cmd_lst)
	{
		handle_empty_args(cmd_lst);
		if (cmd_lst->args && cmd_lst->args[0][0] != '\0')
			process_command(cmd_lst, info);
		cmd_lst = cmd_lst->next;
	}
}
