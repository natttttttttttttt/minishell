/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pibouill <pibouill@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 15:34:10 by pibouill          #+#    #+#             */
/*   Updated: 2024/10/10 21:15:54 by pibouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

/*
** Allocates memory for nmemb elements of size bytes each
** Memory is set to 0
*/

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*new;
	int		total_bytes;

	if (nmemb == 0 || size == 0)
		return (malloc(0));
	total_bytes = nmemb * size;
	if (total_bytes / size != nmemb)
		return (NULL);
	new = malloc(size * nmemb);
	if (new == NULL)
		return (NULL);
	ft_bzero(new, nmemb * size);
	return (new);
}
