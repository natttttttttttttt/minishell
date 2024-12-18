/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pibouill <pibouill@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 15:12:02 by pibouill          #+#    #+#             */
/*   Updated: 2023/10/23 11:11:51 by pibouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Returns first difference between memory areas
** Within n bytes
*/

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*str1;
	unsigned char	*str2;
	size_t			i;

	str1 = (unsigned char *) s1;
	str2 = (unsigned char *) s2;
	i = 0;
	while (i < n)
	{
		if (str1[i] != str2[i])
			return (str1[i] - str2[i]);
		i++;
	}
	return (0);
}

// int	main()
// {
// 	char	str[] = "test string";
// 	char	str2[] = "test stringt";

// 	printf("result of comparison is: %i\n", ft_memcmp(str, str2, 12));
// 	printf("result of comparison is: %i\n", memcmp(str, str2, 12));
// 	return (0);
// }
