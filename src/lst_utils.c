/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pibouill <pibouill@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 11:05:24 by pibouill          #+#    #+#             */
/*   Updated: 2024/12/07 11:07:26 by pibouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_token	*lst_create(char *str, t_type type)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->txt = ft_strdup(str);
	new->type = type;
	new->prev = NULL;
	new->next = NULL;
	return (new);
}

t_token	*ft_lstlast(t_token *lst)
{
	if (lst)
	{
		while (lst->next != NULL)
			lst = lst->next;
	}
	return (lst);
}

void	lst_add_back(t_token **lst, t_token *new)
{
	if (new)
	{
		if (*lst)
		{
			new->prev = ft_lstlast(*lst);
			ft_lstlast(*lst)->next = new;
		}
		else
			*lst = new;
	}
}

void	print_list(t_token *lst)
{
	t_token	*node;

	node = lst; 
	
	while (node->next)
	{
		printf("%s %i\n", (node->txt), node->type);
		node = node->next;
	}
}

void	del_arg(char **args)
{
	int	i;

	if (args == NULL || args[0] == NULL)
		return ;
	free(args[0]);
	i = 0;
	while (args[i] != NULL)
	{
		args[i] = args[i + 1];
		i++;
	}
}
