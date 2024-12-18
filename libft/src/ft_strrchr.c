/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pibouill <pibouill@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 14:06:09 by pibouill          #+#    #+#             */
/*   Updated: 2024/12/18 12:55:50 by pibouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

/*
** Returns a pointer to last occurence of c in *s
*/

char	*ft_strrchr(const char *str, int c)
{
	int	l;

	l = (int)ft_strlen((char *)str);
	while (l >= 0)
	{
		if (str[l] == (char)c)
			return ((char *)(str + l));
		l--;
	}
	return (NULL);
}

// int	main()
// {
// 	char	str[] = "fndsfl";
// 	printf("%s\n", ft_strrchr(str, 'e'));
// 	printf("%s\n", strrchr(str, 'e'));
// 	return (0);
// }
