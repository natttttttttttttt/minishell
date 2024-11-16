/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_digitcount.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pibouill <pibouill@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 15:30:29 by pibouill          #+#    #+#             */
/*   Updated: 2024/10/10 21:15:55 by pibouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

/*
** counts the number of digits of a number,
** based on its base (including minus sign if sign = 1)
*/

int	ft_digitcount(long nb, int base, int sign)
{
	int	i;

	i = 0;
	if (nb == 0)
		return (1);
	if (sign == 1 && nb < 0)
		i++;
	while (nb != 0)
	{
		nb /= base;
		i++;
	}
	return (i);
}
