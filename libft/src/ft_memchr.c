/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pibouill <pibouill@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 14:52:06 by pibouill          #+#    #+#             */
/*   Updated: 2024/10/10 21:16:04 by pibouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

/*
** Looks for c in memory area s
** n bytes are searched
*/

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*str;
	unsigned char	to_find;
	size_t			i;

	str = (unsigned char *) s;
	to_find = (unsigned char) c;
	i = 0;
	while (i < n)
	{
		if (str[i] == to_find)
			return (str + i);
		i++;
	}
	return (NULL);
}

// int	main()
// {
// 	char	str[] = "im the string where O something is hidding";

// 	printf("%p <- is the result\n", ft_memchr(str, 'O', 30));
// 	printf("%p <- is the result\n", memchr(str, 'O', 30));
// 	return (0);
// }
