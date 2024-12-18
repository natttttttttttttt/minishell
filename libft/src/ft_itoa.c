/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pibouill <pibouill@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 12:37:23 by pibouill          #+#    #+#             */
/*   Updated: 2024/12/18 12:55:28 by pibouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

/*
** Returns the (char *) representation of int n
*/

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
