/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pibouill <pibouill@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 13:27:32 by pibouill          #+#    #+#             */
/*   Updated: 2024/10/10 21:16:04 by pibouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

/*
** Copies n bytes from src to dest
** Handles memory overlapping
*/

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*r_dest;
	unsigned char	*r_src;

	r_dest = (unsigned char *)dest;
	r_src = (unsigned char *)src;
	if (dest == NULL && src == NULL)
		return (NULL);
	if (r_src < r_dest)
	{
		while (n-- > 0)
			r_dest[n] = r_src[n];
	}
	else
		ft_memcpy(r_dest, r_src, n);
	return (r_dest);
}
