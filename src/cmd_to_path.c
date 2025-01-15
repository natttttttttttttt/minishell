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

char	*get_cmd(t_info *info, char *cmd)
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
