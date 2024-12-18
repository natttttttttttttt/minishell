/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pibouill <pibouill@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 16:22:09 by pibouill          #+#    #+#             */
/*   Updated: 2023/10/23 12:25:12 by pibouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

/*
** Duplicates *s
*/

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
