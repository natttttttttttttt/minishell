/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pibouill <pibouill@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 14:21:14 by pibouill          #+#    #+#             */
/*   Updated: 2024/10/10 21:16:03 by pibouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

/*
** Deletes and frees every node of lst
*/

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	if (lst == NULL || (*lst) == NULL || del == NULL)
		return ;
	ft_lstclear(&(*lst)->next, del);
	(del)((*lst)->content);
	free(*lst);
	*lst = NULL;
}
