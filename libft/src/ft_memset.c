/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pibouill <pibouill@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 11:23:47 by pibouill          #+#    #+#             */
/*   Updated: 2024/10/10 21:16:04 by pibouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

/*
** Sets n bytes of memory area s to c
*/

void	*ft_memset(void *s, int c, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		((unsigned char *)s)[i] = (unsigned char) c;
		i++;
	}
	return (s);
}

// int	main()
// {
// 	char	str[100];
// 	char	str2[100];

// 	ft_memset(str, 'o', 20);
// 	memset(str2, 'o', 20);
// 	printf("%s\n", str);
// 	printf("%s\n", str2);
// 	return (0);
// }
