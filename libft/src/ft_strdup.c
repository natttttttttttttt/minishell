/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pibouill <pibouill@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 16:22:09 by pibouill          #+#    #+#             */
/*   Updated: 2024/11/11 16:58:10 by pibouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

/*
** Duplicates *s
*/

//char	*ft_strdup(const char *s)
//{
//    char	*new;
//    int		i;

//    i = 0;
//    new = malloc(sizeof(char) * ft_strlen(s) + 1);
//    if (new == NULL)
//        return (NULL);
//    while (*s)
//        new[i++] = *s++;
//    new[i] = '\0';
//    return (new);
//}

char	*ft_strdup(const char *src)
{
	char	*str;
	int		i;

	if (!src)
		return (NULL);
	i = 0;
	if (src[0] == '\0')
		str = malloc(1);
	else
	{
		while (src[i])
			i++;
		str = malloc((i + 1) * sizeof(char));
		i = 0;
		while (src[i])
		{
			str[i] = src[i];
			i++;
		}
	}
	str[i] = '\0';
	return (str);
}
