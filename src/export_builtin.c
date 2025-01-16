/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntsvetko <ntsvetko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 13:01:34 by pibouill          #+#    #+#             */
/*   Updated: 2024/11/25 17:05:11 by ntsvetko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	process_export_arg(char *arg, t_info *info)
{
	char	**split;
	char	*var;
	char	*value;
	int		ret;

	split = ft_split(arg, '=');
	if (!split)
		return (12); // don't need to be free here?
	var = split[0];
	value = split[1];
	ret = 0;
	if (valid_var_name(var))
	{
		if (value || arg[ft_strlen(arg) - 1] == '=')
			update_env(var, value, &(info->my_envp));
	}
	else
	{
		printf("export: %s: not a valid identifier\n", var);
		ret = 1;
	}
	return (ret);
}

void	free_split(char **split)
{
	free(split[0]);
	if (split[1])
		free(split[1]);
	free(split);
}

int	export_builtin(char **args, t_info *info, int i)
{
	int		ret;
	int		f;

	f = 0;
	while (args[i])
	{
		ret = process_export_arg(args[i], info);
		if (ret == 12)
			return (ret);
		if (ret == 1)
			f = 1;
		free_split(ft_split(args[i], '='));
		i++;
	}
	return (f);
}
