/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pibouill <pibouill@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 13:01:34 by pibouill          #+#    #+#             */
/*   Updated: 2024/11/24 13:03:12 by pibouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// should I still norminette this one?
static char	**split_for_export(char *s)
{
	int		i;
	int		l;
	char	**res;

	l = ft_strlen(s);
	res = malloc(sizeof(char *) * 3);
	if (!res)
	{
		perror("malloc");
		return (NULL);
	}
	res[2] = NULL;
	i = 0;
	while (s[i] && s[i] != '=')
		i++;
	if (s[i] == '=')
	{
		res[0] = malloc(sizeof(char) * (i + 1));
		if (!res[0])
		{
			perror("malloc");
			return (NULL);
		}
		ft_strncpy(res[0], s, i);
		if (s[i + 1])
		{
			res[1] = malloc(sizeof(char) * (l - i));
			if (!res[1])
			{
				perror("malloc");
				return (NULL);
			}
			ft_strncpy(res[1], s + i + 1, l - i - 1);
		}
	}
	else
	{
		res[0] = ft_strdup(s);
		res[1] = NULL;
	}
	return (res);
}

int	export_builtin(char **args, t_info *info, int i)
{
	char	**split;
	char	*var;
	char	*value;
	int		f;

	f = 0;
	while (args[i])
	{
		split = split_for_export(args[i]);
		if (!split)
			return (12);
		var = split[0];
		if (split[1] != NULL)
			value = split[1];
		else
			value = "";
		if (valid_var_name(var))
		{
			if (value || args[i][ft_strlen(args[i]) - 1] == '=')
				update_env(var, value, &(info->my_envp));
		}
		else
		{
			printf("export: %s: not a valid identifier\n", var);
			f = 1;
		}
		free(split[0]);
		if (split[1])
			free(split[1]);
		free(split);
		i++;
	}
	return (f);
}
