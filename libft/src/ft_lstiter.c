/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pibouill <pibouill@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 14:34:52 by pibouill          #+#    #+#             */
/*   Updated: 2024/10/10 21:16:03 by pibouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

/*
** Applies f function to each node of lst
*/

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	if (f == NULL || lst == NULL)
		return ;
	while (lst)
	{
		f(lst->content);
		lst = lst->next;
	}
}
