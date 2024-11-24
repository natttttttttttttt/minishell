/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pibouill <pibouill@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 13:04:11 by pibouill          #+#    #+#             */
/*   Updated: 2024/11/24 13:04:27 by pibouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	unset_builtin(char **args, t_info *info, int i, int j)
{
	int		n;
	int		k;
	int		remove;
	char	**new_env;

	if (args[1] == NULL)
		return (0);
	while (args[i] && find_env_var(info->my_envp, args[i]) != -1)
	{
		j++;
		i++;
	}
	n = 0;
	while (info->my_envp[n] != NULL)
		n++;
	new_env = malloc(sizeof(char *) * (n + 1 - j));
	if (!new_env)
	{
		perror("malloc");
		return (errno);
	}
	i = 0;
	j = 0;
	while (i < n)
	{
		remove = 0;
		k = 1;
		while (args[k])
		{
			if (ft_strncmp(info->my_envp[i], args[k], ft_strlen(args[k])) == 0
				&& info->my_envp[i][ft_strlen(args[k])] == '=')
			{
				remove = 1;
				break ;
			}
			k++;
		}
		if (!remove)
			new_env[j++] = info->my_envp[i];
		i++;
	}
	new_env[j] = NULL;
	free(info->my_envp);
	info->my_envp = new_env;
	return (0);
}
