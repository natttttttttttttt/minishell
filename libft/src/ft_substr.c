/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pibouill <pibouill@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 16:43:46 by pibouill          #+#    #+#             */
/*   Updated: 2024/12/18 12:54:42 by pibouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

/*
** Creates new string from *s
** Starting at index start and of size len
*/

char	*ft_substr(char *s, int start, int len)
{
	int		size;
	char	*res;
	int		i;

	if (start >= ft_strlen(s))
		return (NULL);
	size = ft_strlen(s) - start;
	if (size < len)
		len = size;
	res = (char *)malloc((len + 1) * sizeof(char));
	if (!s || !res)
		return (NULL);
	i = 0;
	while (i < len)
	{
		res[i] = s[i + start];
		i++;
	}
	res[i] = '\0';
	return (res);
}

// int	main()
// {
// 	char	str[] = "hola";

// 	printf("%s\n", ft_substr(str, 2, 535));
// 	return (0);
// }
