/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pibouill <pibouill@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 14:06:09 by pibouill          #+#    #+#             */
/*   Updated: 2023/10/27 11:42:50 by pibouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Returns a pointer to last occurence of c in *s
*/

char	*ft_strrchr(const char *s, int c)
{
	int	i;

	i = ft_strlen(s);
	while (i >= 0)
	{
		if (s[i] == (unsigned char) c)
			return ((char *)(s + i));
		i--;
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
