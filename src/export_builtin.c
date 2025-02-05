/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntsvetko <ntsvetko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 13:01:34 by pibouill          #+#    #+#             */
/*   Updated: 2025/02/05 15:45:48 by pibouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// void	print_string_array(char **arr)
// {
// 	if (arr == NULL) {
// 		printf("NULL\n");
// 		return;
// 	}
// 	for (int i = 0; arr[i] != NULL; i++) {
// 		printf("%s ", arr[i]);
// 	}
// 	printf("\n");
//
// }

char	**split_export(char *arg)
{
	char	**split;
	int		i;

	split = malloc(sizeof(char *) * 3);
	split[0] = NULL;
	split[1] = NULL;
	split[2] = NULL;
	i = 0;
	if (arg[0] == '=' || !ft_strchr(arg, '='))
	{
		split[0] = ft_strdup(arg);
		return (split);
	}
	split[0] = malloc(ft_strchr(arg, '=') - arg + 1);
	while (*arg != '=')
		split[0][i++] = *(arg++);
	split[0][i] = '\0';
	if (*(++arg))
	{
		split[1] = malloc(ft_strlen(arg) + 1);
		ft_strncpy(split[1], arg, ft_strlen(arg));
	}
	return (split);
}

void	free_split(char **split)
{
	free(split[0]);
	if (split[1])
		free(split[1]);
	free(split);
}

int	process_export_arg(char *arg, t_info *info)
{
	char	**split;
	char	*var;
	char	*value;
	int		ret;

	split = split_export(arg);
	if (!split)
		return (12);
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
	free_split(split);
	return (ret);
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
		i++;
	}
	return (f);
}
