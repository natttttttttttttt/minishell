/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pibouill <pibouill@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 15:32:03 by pibouill          #+#    #+#             */
/*   Updated: 2023/11/15 15:03:42 by pibouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

/*
** Returns first difference between *s1 and *s2
** Within n bytes
*/

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

// int	main()
// {
// 	char str3[] = "test\200";
// 	// char str4[] = "test\0";
// 	printf("%i\n", ft_strncmp(str3, "test\0", 10));
// 	printf("%i\n", strncmp(str3, "test\0", 10));
// 	printf("%i\n", ft_strncmp("test-a", "test-A", 10));
// 	printf("%i\n", strncmp("test-a", "test-A", 10));
// 	return (0);
// }
