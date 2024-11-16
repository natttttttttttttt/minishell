/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pibouill <pibouill@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 10:36:34 by pibouill          #+#    #+#             */
/*   Updated: 2024/10/10 21:16:04 by pibouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"
#include <string.h>

/*
** Copies n bytes from src to dest
*/

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char			*c_dst;
	char			*c_src;
	size_t			i;

	c_dst = (char *)dest;
	c_src = (char *)src;
	i = 0;
	if (dest == NULL && src == NULL)
		return (NULL);
	while (i < n)
	{
		c_dst[i] = c_src[i];
		i++;
	}
	return (c_dst);
}

// int	main()
// {
// 	char src[] = "im the source";
// 	char dst[] = "destination";
// 	char src2[] = "im the source";
// 	char dst2[] = "destination";

// 	printf("\ndst before memcpy : %s\n", dst);
// 	memcpy(dst, src, 7);
// 	printf("\n\ndst after memcpy: %s\n", dst);

// 	printf("\nwhat was copied : ");
// 	for(size_t i = 0; i < sizeof(dst); i++)
// 		printf("%c", dst[i]);

// 	printf("\n\ndst2 before ft_memcpy : %s\n", dst2);
// 	ft_memcpy(dst2, src2, 7);

// 	printf("dst2 after ft_memcpy: %s\n", dst2);

// 		printf("\nwhat was copied : ");
// 	for(size_t i = 0; i < sizeof(dst2); i++)
// 		printf("%c", dst2[i]);
// }
