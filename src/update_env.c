/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pibouill <pibouill@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 16:11:38 by pibouill          #+#    #+#             */
/*   Updated: 2025/01/08 16:12:38 by pibouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	*safe_return(void *ptr)
{
	if (ptr == NULL)
		perror("malloc");
	return (ptr);
}

char	*create_env_string(char *var, char *value)
{
	char	*s;
	int		i;

	s = malloc(sizeof(char)
				* (ft_strlen(var) + ft_strlen(value) + 2));
	if (!s)
		return (NULL);
	i = 0;
	while (i < ft_strlen(var))
	{
		s[i] = var[i];
		i++;
	}
	s[i++] = '=';
	while (i < ft_strlen(var) + ft_strlen(value) + 1)
	{
		s[i] = value[i - ft_strlen(var) - 1];
		i++;
	}
	s[i] = '\0';
	return (s);
}

char	**create_new_envp(char **old_envp, char *new_var)
{
	char	**new_envp;
	int		i;

	i = 0;
	while (old_envp[i])
		i++;
	new_envp = malloc((i + 2) * sizeof(char *));
	if (!new_envp)
		return (NULL);
	i = 0;
	while (old_envp[i])
	{
		new_envp[i] = old_envp[i];
		i++;
	}
	new_envp[i] = ft_strdup(new_var);
	new_envp[i + 1] = NULL;
	return (new_envp);
}

void	update_env(char *var, char *value, char ***my_envp)
{
	char	*s;
	char	**new_envp;
	int		var_i;

	s = create_env_string(var, value);
	if (!s)
		return ((void)perror("malloc"));
	var_i = find_env_var(*my_envp, var);
	if (var_i != -1)
	{
		free((*my_envp)[var_i]);
		(*my_envp)[var_i] = s;
	}
	else
	{
		new_envp = create_new_envp(*my_envp, s);
		free(s);
		if (!new_envp)
			return ((void)perror("malloc"));
		free(*my_envp);
		*my_envp = new_envp;
	}
}
