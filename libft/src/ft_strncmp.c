/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pibouill <pibouill@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 15:32:03 by pibouill          #+#    #+#             */
/*   Updated: 2024/10/10 21:16:05 by pibouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

/*
** Returns first difference between *s1 and *s2
** Within n bytes
*/

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while (s1[i] && i < n - 1)
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
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
