/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pibouill <pibouill@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 13:53:10 by pibouill          #+#    #+#             */
/*   Updated: 2025/01/08 16:12:41 by pibouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	**copy_envp(char **envp)
{
	int		i;
	int		n;
	int		j;
	char	**my_envp;

	i = 0;
	n = 0;
	while (envp[n] != NULL)
		n++;
	my_envp = malloc((n + 1) * sizeof(char *));
	if (!my_envp)
		return (NULL);
	while (i < n)
	{
		my_envp[i] = ft_strdup(envp[i]);
		if (!my_envp[i])
		{
			j = 0;
			while (j < i)
			{
				free(my_envp[j]);
				j++;
			}
			free(my_envp);
			return (NULL);
		}
		i++;
	}
	my_envp[n] = NULL;
	return (my_envp);
}

char	*ft_getenv(char **my_envp, char *var)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(var);
	while (my_envp[i] != NULL)
	{
		if (ft_strncmp(my_envp[i], var, len) == 0 && my_envp[i][len] == '=')
			return (my_envp[i] + len + 1);
		i++;
	}
	return (NULL);
}

int	find_env_var(char **my_envp, char *var)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(var);
	while (my_envp[i])
	{
		if (ft_strncmp(my_envp[i], var, len) == 0 && my_envp[i][len] == '=')
			return (i);
		i++;
	}
	return (-1);
}
