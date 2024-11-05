/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pibouill <pibouill@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 16:31:33 by pibouill          #+#    #+#             */
/*   Updated: 2024/11/05 16:32:13 by pibouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*ft_strdup(const char *src)
{
	char	*str;
	int		i;

	if (!src)
		return (NULL);
	i = 0;
	if (src[0] == '\0')
		str = malloc(1);
	else
	{
		while (src[i])
			i++;
		str = malloc((i + 1) * sizeof(char));
		i = 0;
		while (src[i])
		{
			str[i] = src[i];
			i++;
		}
	}
	str[i] = '\0';
	return (str);
}

int	ft_strlen(const char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strchr(char *str, int c)
{
	char	*st;

	st = (char *)str;
	if (c == 0)
		return (st + ft_strlen(str));
	while (*st)
	{
		if (*st == (char)c)
			return (st);
		st++;
	}
	return (NULL);
}

int	ft_isalnum(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	all_digits(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (str[i] == '\0')
		return (0);
	while (str[i])
	{
		if (str[i] >= '0' && str[i] <= '9')
			i++;
		else
			return (0);
	}
	return (1);
}
