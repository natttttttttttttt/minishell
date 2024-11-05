/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pibouill <pibouill@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 16:33:43 by pibouill          #+#    #+#             */
/*   Updated: 2024/11/05 16:34:55 by pibouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_atoi(char *str)
{
	int	i;
	int	n;
	int	sign;

	i = 0;
	n = 0;
	sign = 1;
	while ((str[i] == 32) || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] != '\0' && (str[i] >= '0' && str[i] <= '9'))
	{
		n *= 10;
		n += str[i] - '0';
		i++;
	}
	return (n * sign);
}

int	ft_strncmp(char *str1, char *str2, size_t n)
{
	unsigned char	*s1;
	unsigned char	*s2;

	s1 = (unsigned char *)str1;
	s2 = (unsigned char *)str2;
	while ((*s1 || *s2) && *s1 == *s2 && n - 1 > 0)
	{
		n--;
		s1++;
		s2++;
	}
	if (n != 0)
		return (*s1 - *s2);
	return (0);
}

void ft_strncpy(char *dest, const char *src, int size)
{
	int	i;

	i = 0;
	if (size != 0)
	{
		while (src[i] != '\0' && i < size)
		{
			dest[i] = src[i];
			i++;
		}
		dest[i] = '\0';
	}
}

char	*ft_substr(char *s, int start, int len)
{
	int		size;
	char	*res;
	int		i;

	if (start >= ft_strlen(s))
		return (NULL);
	size = ft_strlen(s) - start;
	if (size < len)
		len = size;
	res = (char *)malloc((len + 1) * sizeof(char));
	if (!s || !res)
		return (NULL);
	i = 0;
	while (i < len)
	{
		res[i] = s[i + start];
		i++;
	}
	res[i] = '\0';
	return (res);
}
