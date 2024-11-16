/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pibouill <pibouill@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 17:19:53 by pibouill          #+#    #+#             */
/*   Updated: 2024/10/10 21:16:06 by pibouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

/*
** Trims *s1 from chars in *set
*/

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t		len;
	char		*trimmed;

	if (s1 == NULL)
		return (NULL);
	while (*s1 && ft_strchr(set, *s1))
		s1++;
	len = ft_strlen(s1);
	while (len > 0 && ft_strchr(set, s1[len]))
		len--;
	trimmed = ft_substr(s1, 0, len + 1);
	return (trimmed);
}

// int	main()
// {
// 	char	s1[] = ".,.,.,teste, bla ,.,.";
// 	char	set[] = ",.";

// 	printf("%s\n", ft_strtrim(s1, set));
// 	return (0);
// }
