/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pibouill <pibouill@student.42prague.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 17:40:26 by pibouill          #+#    #+#             */
/*   Updated: 2024/10/10 21:15:47 by pibouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

static int	is_valid_char(char c)
{
	return ((c >= 'a' && c <= 'f')
		|| (c >= 'A' && c <= 'F') || (c >= '0' && c <= '9'));
}

static int	is_hex_prefix(const char *prefix)
{
	return (*prefix == '0' && *(prefix + 1) == 'x');
}

int	ft_atoi_base(const char *str, unsigned int base)
{
	int	ret;
	int	sign;

	ret = 0;
	sign = 1;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign *= -1;
		str++;
	}
	if (is_hex_prefix(str) == 1)
		str += 2;
	while (*str && is_valid_char(*str))
	{
		if (*str >= '0' && *str <= '9')
			ret = ret * base + *str - '0';
		if (*str >= 'a' && *str <= 'f')
			ret = ret * base + *str - 'a' + 10;
		if (*str >= 'A' && *str <= 'F')
			ret = ret * base + *str - 'A' + 10;
		str++;
	}
	return (ret * sign);
}

/*int	main()
{
	printf("%d\n", ft_atoi_base("0x810202", 16));
	printf("%d\n", ft_atoi_base("0xFFFFFF", 16));
	printf("%d\n", ft_atoi_base("10", 2));
	printf("%d\n", ft_atoi_base("42f", 16));
}*/
