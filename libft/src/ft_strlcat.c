/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pibouill <pibouill@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 16:27:59 by pibouill          #+#    #+#             */
/*   Updated: 2024/10/10 21:16:05 by pibouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

/*
** Concatenates src to dst
** Ends dst with \0
** Returns length of the result string whether it was possible or not
** If src was completely concatenated, return value will be smaller than size
*/

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	src_len;
	size_t	dest_len;
	size_t	i;

	if (dst == NULL && size == 0)
		return (0);
	i = 0;
	dest_len = ft_strlen(dst);
	src_len = ft_strlen(src);
	if (size <= dest_len)
		return (size + src_len);
	while (src[i] && (dest_len + i) < (size - 1))
	{
		dst[dest_len + i] = src[i];
		i++;
	}
	dst[dest_len + i] = '\0';
	return (dest_len + src_len);
}

// #include <bsd/string.h>
// int	main()
// {
// 	char	src[] = "abc";
// 	char	dst[] = "";

// 	printf("ft_strlcat returns %zu\n", ft_strlcat(dst, src, 0));
// 	printf("strlcat returns %zu\n", strlcat(dst, src, 0));
// 	return (0);
// }
