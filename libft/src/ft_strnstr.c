/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pibouill <pibouill@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 16:01:16 by pibouill          #+#    #+#             */
/*   Updated: 2024/10/10 21:16:05 by pibouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

/*
** Searches for str little in str big
** Within len bytes
*/

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if ((little == NULL && len == 0) || *little == '\0')
		return ((char *)big);
	if (big == NULL && len == 0)
		return (NULL);
	while (big[i] && i < len)
	{
		j = 0;
		while (little[j] == big[i + j] && (i + j) < len)
		{
			if (little[j + 1] == '\0')
				return ((char *)big + i);
			j++;
		}
		i++;
	}
	return (NULL);
}

// int	main()
// {
// 	char	big[] = "im am the haystack";
// 	char	little[] = "hay";
// 	printf("%s\n", ft_strnstr(big, little, -1));
// 	printf("%s\n", strnstr(big, little, -1));
// 	return (0);
// }
