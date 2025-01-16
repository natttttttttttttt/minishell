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
			return (free(tmp), try);
		free(try);
		free(tmp);
		i++;
	}
	printf("%s: command not found\n", cmd);
	info->exit_code = 127;
	return (ft_strdup(""));
}
