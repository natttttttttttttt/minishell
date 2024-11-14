/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_cmd_arg.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pibouill <pibouill@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 12:38:53 by pibouill          #+#    #+#             */
/*   Updated: 2024/11/14 12:39:16 by pibouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	end_alloc_cmd_arg(char ***arr, char *arg, int i, char **tmp)
{
	int	j;

	j = 0;
	while (j < i)
	{
		(*arr)[j] = tmp[j];
		j++;
	}
	(*arr)[i] = ft_strdup(arg);
	(*arr)[i + 1] = NULL;
	free(tmp);
}

void	alloc_cmd_arg(char ***arr, char *arg)
{
	int		i;
	int		j;
	char	**tmp;

	i = 0;
	j = 0;
	while ((*arr)[i])
		i++;
	tmp = (char **)malloc(sizeof(char *) * (i + 1));
	if (!tmp)
		return ;
	while (j < i)
	{
		tmp[j] = (*arr)[j];
		j++;
	}
	free(*arr);
	*arr = (char **)malloc(sizeof(char *) * (i + 2));
	if (!arr)
		return (free(tmp));
	end_alloc_cmd_arg(arr, arg, i, tmp);
}

void	add_cmd_arg(char ***arr, char *arg)
{
	char	**tmp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (*arr)
	{
		alloc_cmd_arg(arr, arg);
		//while ((*arr)[i])
		//    i++;
		//tmp = (char **)malloc(sizeof(char *) * (i + 1));
		//if (!tmp)
		//    return ;
		//while (j < i)
		//{
		//    tmp[j] = (*arr)[j];
		//    j++;
		//}
		//free(*arr);
		//*arr = (char **)malloc(sizeof(char *) * (i + 2));
		//if (!arr)
		//    return (free(tmp));
		//j = 0;
		//while (j < i)
		//{
		//    (*arr)[j] = tmp[j];
		//    j++;
		//}
		//(*arr)[i] = ft_strdup(arg);
		//(*arr)[i + 1] = NULL;
		//free(tmp);
	}
	else
	{
		(*arr) = (char **)malloc(sizeof(char *) * 2);
		if (!(*arr))
			return ;
		(*arr)[0] = ft_strdup(arg);
		(*arr)[1] = NULL;
	}
}
