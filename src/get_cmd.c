/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_to_path_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pibouill <pibouill@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 15:09:14 by pibouill          #+#    #+#             */
/*   Updated: 2025/01/16 15:09:28 by pibouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// create helper function that does what the while loop does in get_cmd
// char	*get_cmd(t_info *info, char *cmd)
// {
// 	char	*try;
// 	char	*tmp;
// 	int		i;
//
// 	i = 0;
// 	while (info->paths[i])
// 	{
// 		tmp = ft_strjoin(info->paths[i], "/");
// 		if (!tmp)
// 			return (perror("Alloc failed for tmp"), ft_strdup(""));
// 		try = ft_strjoin(tmp, cmd);
// 		if (!try)
// 			return (perror("Alloc failed for try"), ft_strdup(""));
// 		if (access(try, X_OK) == 0)
// 			return (free(tmp), try);
// 		free(try);
// 		free(tmp);
// 		i++;
// 	}
// 	if (!ft_strncmp("./", cmd, 2) && access(cmd, X_OK) != 0)
// 	{
// 		perror(cmd);
// 		info->exit_code = 126;
// 	}
// 	else
// 	{
// 		printf("%s: command not found\n", cmd);
// 		info->exit_code = 127;
// 	}
// 	return (ft_strdup(""));
// }

char	*join_path_and_cmd(char *path, char *cmd)
{
	char	*tmp;
	char	*full_path;

	tmp = ft_strjoin(path, "/");
	if (!tmp)
	{
		perror("Alloc failed for tmp");
		return (NULL);
	}
	full_path = ft_strjoin(tmp, cmd);
	free(tmp);
	if (!full_path)
	{
		perror("Alloc failed for full_path");
		return (NULL);
	}
	return (full_path);
}

char	*handle_accessible_path(char *path, char *tmp)
{
	free(tmp);
	return (path);
}

void	handle_command_error(t_info *info, char *cmd)
{
	if (!ft_strncmp("./", cmd, 2) && access(cmd, X_OK) != 0)
	{
		perror(cmd);
		info->exit_code = 126;
	}
	else
	{
		printf("%s: command not found\n", cmd);
		info->exit_code = 127;
	}
}

char	*get_cmd(t_info *info, char *cmd)
{
	char	*try;
	int		i;

	i = 0;
	while (info->paths[i])
	{
		try = join_path_and_cmd(info->paths[i], cmd);
		if (!try)
			return (ft_strdup(""));
		if (access(try, X_OK) == 0)
			return (handle_accessible_path(try, NULL));
		free(try);
		i++;
	}
	handle_command_error(info, cmd);
	return (ft_strdup(""));
}
