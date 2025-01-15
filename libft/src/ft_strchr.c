/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pibouill <pibouill@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 13:54:38 by pibouill          #+#    #+#             */
/*   Updated: 2024/05/24 15:03:55 by pibouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

/*
** Returns pointer to first c in *s
*/

char	*ft_strchr(const char *str, int c)
{
	char	*st;

	if (str == NULL)
		return (NULL);
	st = (char *)str;
	if (c == 0)
		return (st + ft_strlen(str));
	while (*st)
	{
		if (*st == (char)c)
			return (st);
		st++;
	}
	return (NULL);
}

// int	main()
// {
// 	char	str[] = "teste";
// 	printf("%s\n", ft_strchr(str, '\0'));
// 	printf("%s\n", strchr(str, '\0'));
// 	return (0);
// }
