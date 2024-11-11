/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pibouill <pibouill@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 16:18:44 by pibouill          #+#    #+#             */
/*   Updated: 2024/11/11 17:00:19 by pibouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_token	*toklst_create(char *str, t_type type)
{
	t_token	*new;

	new = (t_token *)malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->txt = ft_strdup(str);
	new->type = type;
	new->prev = NULL;
	new->next = NULL;
	return (new);
}

t_token	*toklst_last(t_token *lst)
{
	if (lst)
	{
		while (lst->next != NULL)
			lst = lst->next;
	}
	return (lst);
}

void	toklst_add_back(t_token **lst, t_token *new)
{
	if (new)
	{
		if (*lst)
		{
			new->prev = toklst_last(*lst);
			toklst_last(*lst)->next = new;
		}
		else
			*lst = new;
	}
}

void	print_list(t_token *lst)
{
	t_token	*node;

	node = lst;
	while (node->type != DONE)
	{
		printf("%s %i\n", (node->txt), node->type);
		node = node->next;
	}
}
