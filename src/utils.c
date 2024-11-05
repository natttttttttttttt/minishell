/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pibouill <pibouill@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 16:29:41 by pibouill          #+#    #+#             */
/*   Updated: 2024/11/05 16:34:41 by pibouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	ft_len(int n)
{
	int	l;

	l = 1;
	if (n < 0)
	{
		n *= -1;
		l++;
	}
	while (n / 10 > 0)
	{
		l++;
		n = n / 10;
	}
	return (l);
}

char	*ft_itoa(int n)
{
	char	*res;
	int		l;

	l = ft_len(n);
	res = (char *)malloc((l + 1) * sizeof(char));
	if (!res)
		return (NULL);
	res[l] = '\0';
	l--;
	while (l >= 0)
	{
		res[l] = (n % 10) + '0';
		n = n / 10;
		l--;
	}
	return (res);
}

char	*ft_strrchr(const char *str, int c)
{
	int	l;

	l = (int)ft_strlen((char *)str);
	while (l >= 0)
	{
		if (str[l] == (char)c)
			return ((char *)(str + l));
		l--;
	}
	return (NULL);
}
