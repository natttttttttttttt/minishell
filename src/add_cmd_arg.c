/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_cmd_arg.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pibouill <pibouill@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 16:44:08 by pibouill          #+#    #+#             */
/*   Updated: 2025/01/08 16:44:39 by pibouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	init_new_arg(char ***arr, char *arg)
{
	(*arr) = (char **)malloc(sizeof(char *) * 2);
	if (!(*arr))
		return ;
	(*arr)[0] = ft_strdup(arg);
	(*arr)[1] = NULL;
}

static char	**create_temp_array(char **arr, int size)
{
	char	**tmp;
	int		j;

	tmp = (char **)malloc(sizeof(char *) * size);
	if (!tmp)
		return (NULL);
	j = 0;
	while (j < size - 1)
	{
		tmp[j] = arr[j];
		j++;
	}
	return (tmp);
}

static bool	reallocate_array(char ***arr, char **tmp, int size)
{
	int	j;

	*arr = (char **)malloc(sizeof(char *) * (size + 1));
	if (!arr)
	{
		free(tmp);
		return (false);
	}
	j = 0;
	while (j < size - 1)
	{
		(*arr)[j] = tmp[j];
		j++;
	}
	return (true);
}

void	add_cmd_arg(char ***arr, char *arg)
{
	char	**tmp;
	int		i;

	i = 0;
	if (!*arr)
	{
		init_new_arg(arr, arg);
		return ;
	}
	while ((*arr)[i])
		i++;
	tmp = create_temp_array(*arr, i + 1);
	if (!tmp)
		return ;
	free(*arr);
	if (!reallocate_array(arr, tmp, i + 1))
		return ;
	(*arr)[i] = ft_strdup(arg);
	(*arr)[i + 1] = NULL;
	free(tmp);
}
