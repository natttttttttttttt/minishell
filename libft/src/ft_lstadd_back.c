/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pibouill <pibouill@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 14:05:57 by pibouill          #+#    #+#             */
/*   Updated: 2024/10/10 21:16:02 by pibouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

/*
** Adds the node new to the end of lst
*/

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*temp_ptr;

	if (new == NULL)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	temp_ptr = ft_lstlast(*lst);
	temp_ptr->next = new;
}
