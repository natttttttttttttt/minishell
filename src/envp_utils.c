/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pibouill <pibouill@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 17:45:42 by pibouill          #+#    #+#             */
/*   Updated: 2024/11/11 17:50:11 by pibouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	free_envp(char **my_envp, int i)
{
	while (i-- > 0)
		free(my_envp[i]);
	free(my_envp);
}

char	**copy_envp(char **envp)
{
	int		i;
	int		n;
	char	**my_envp;

	n = 0;
	while (envp[n])
		n++;
	my_envp = malloc((n + 1) * sizeof(char *));
	if (!my_envp)
		return (NULL);
	i = 0;
	while (i < n)
	{
		my_envp[i] = ft_strdup(envp[i]);
		if (!my_envp[i])
			return (free_envp(my_envp, i), NULL);
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
