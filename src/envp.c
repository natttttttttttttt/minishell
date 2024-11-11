/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pibouill <pibouill@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 16:10:42 by pibouill          #+#    #+#             */
/*   Updated: 2024/11/11 17:50:24 by pibouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	env_size(char **my_envp)
{
	int	size;

	size = 0;
	while (my_envp[size])
		size++;
	return (size);
}

static char	*create_env_entry(char *var, char *value)
{
	char	*s;
	int		i;
	int		len;

	len = ft_strlen(var) + ft_strlen(value) + 2;
	s = malloc(len);
	if (!s)
		return (NULL);
	i = -1;
	while (var[++i])
		s[i] = var[i];
	s[i++] = '=';
	while (*value)
		s[i++] = *value++;
	s[i] = '\0';
	return (s);
}

static char	**resize_envp(char **my_envp, int size)
{
	char	**new_envp;
	int		i;

	new_envp = malloc((size + 1) * sizeof(char *));
	if (!new_envp)
		return (NULL);
	i = -1;
	while (my_envp[++i])
		new_envp[i] = my_envp[i];
	new_envp[i] = NULL;
	return (new_envp);
}

static void	replace_or_add_env(char **my_envp, char *s, int var_i)
{
	if (var_i != -1)
	{
		free(my_envp[var_i]);
		my_envp[var_i] = s;
	}
	else
	{
		while (*my_envp)
			my_envp++;
		*my_envp++ = s;
		*my_envp = NULL;
	}
}

void	update_env(char *var, char *value, char ***my_envp)
{
	int		var_i;
	char	*s;
	char	**new_envp;

	s = create_env_entry(var, value);
	if (!s)
		return (perror("malloc"));
	var_i = find_env_var(*my_envp, var);
	if (var_i == -1)
	{
		new_envp = resize_envp(*my_envp, env_size(*my_envp) + 1);
		if (!new_envp)
			return (free(s), perror("malloc"));
		*my_envp = new_envp;
	}
	replace_or_add_env(*my_envp, s, var_i);
}
