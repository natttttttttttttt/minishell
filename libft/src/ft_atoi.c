/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pibouill <pibouill@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 16:36:35 by pibouill          #+#    #+#             */
/*   Updated: 2024/10/10 21:15:45 by pibouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

/*
** Returns the int representaion of char *nptr
** Skips whitespaces
** 0 if more than one sign
*/

int	ft_atoi(const char *nptr)
{
	int	ret;
	int	sign;

	ret = 0;
	sign = 1;
	while ((*nptr == ' ') || (*nptr >= 9 && *nptr <= 13))
		nptr++;
	if (*nptr == '-' || *nptr == '+')
	{
		if (*nptr == '-')
		{
			sign = -1;
			nptr++;
		}
		else if (*nptr == '+')
			nptr++;
	}
	while (*nptr >= '0' && *nptr <= '9')
	{
		ret = ret * 10 + *nptr - '0';
		nptr++;
	}
	return (ret * sign);
}

	// int	main()
	// {
	// 	char	str[] = "		+--+42jdifj5i";
	// 	printf("%d\n", ft_atoi(str));
	// 	printf("%d\n", atoi(str));
	// 	return (0);
	// }
