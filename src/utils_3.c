/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pibouill <pibouill@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 16:32:43 by pibouill          #+#    #+#             */
/*   Updated: 2024/11/05 16:33:04 by pibouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	free_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr && arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

char	*ft_strjoin(char *s1, const char *s2)
{
	char	*res;
	size_t	len;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;

	len = ft_strlen(s1) + ft_strlen(s2);
	res = (char *)malloc((len + 1) * sizeof(char));
	if (!res)
		return (NULL);
	while (s1 && s1[i])
	{
		res[i] = s1[i];
		i++;
	}
	while (s2 && s2[j])
	{
		res[i + j] = s2[j];
		j++;
	}
	res[i + j] = '\0';
	return (res);
}

static int	count(const char *str, char c)
{
	int	i;
	int	k;

	i = 0;
	k = 0;
	while (str[i])
	{
		if (str[i] != c)
		{
			k++;
			while (str[i] && str[i] != c)
				i++;
		}
		else
			i++;
	}
	return (k);
}

static void	ft_skip(const char *str, char c, int *i, int *from)
{
	while (str[*i] == c)
		(*i)++;
	*from = *i;
	while (str[*i] != c && str[*i])
		(*i)++;
}

char	**ft_split(const char *s, char c)
{
	int		i;
	int		k;
	int		j;
	int		from;
	char	**res;

	i = 0;
	k = 0;
	res = (char **)malloc((count(s, c) + 1) * sizeof(char *));
	if (!res)
		return (NULL);
	while (s[i])
	{
		ft_skip(s, c, &i, &from);
		if (from == i)
			break ;
		res[k] = (char *)malloc((i - from + 1) * sizeof(char));
		j = 0;
		while (from < i)
			res[k][j++] = s[from++];
		res[k][j] = '\0';
		k++;
	}
	res[k] = NULL;
	return (res);
}
