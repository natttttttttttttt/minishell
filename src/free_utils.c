/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pibouill <pibouill@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 11:05:48 by pibouill          #+#    #+#             */
/*   Updated: 2024/12/07 11:06:19 by pibouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	free_token_lst(t_token *head)
{
	t_token	*node;
	t_token	*next;

	node = head;
	while (node != NULL)
	{
		next = node->next;
		free(node->txt);
		free(node);
		node = next;
	}
}

void	free_order(t_order *order)
{
	if (order->input)
		free(order->input);
	if (order->output)
		free(order->output);
	if (order->heredoc)
		free(order->heredoc);
	if (order->append)
		free(order->append);
}

void	free_command_list(t_cmd **head)
{
	t_cmd	*node;
	t_cmd	*next;

	node = *head;
	while (node != NULL)
	{
		next = node->next;
		free_arr(node->args);
		free_arr(node->output);
		free_arr(node->input);
		free_arr(node->append);
		free_arr(node->delimiter);
		free_order(node->order);
		free(node->order);
		free(node);
		node = NULL;
		*head = NULL;
		node = next;
	}
}
