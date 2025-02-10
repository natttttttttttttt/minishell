/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pibouill <pibouill@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 13:45:26 by pibouill          #+#    #+#             */
/*   Updated: 2024/12/06 13:52:13 by pibouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_order	*order_new(void)
{
	t_order	*order;

	order = malloc(sizeof(*order));
	order->input = NULL;
	order->output = NULL;
	order->append = NULL;
	order->heredoc = NULL;
	order->i_input = 0;
	order->i_append = 0;
	order->i_output = 0;
	order->count = 0;
	return (order);
}

t_cmd	*cmd_new(void)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(*cmd));
	cmd->args = NULL;
	cmd->input = NULL;
	cmd->output = NULL;
	cmd->append = NULL;
	cmd->delimiter = NULL;
	cmd->next = NULL;
	cmd->prev = NULL;
	cmd->order = order_new();
	return (cmd);
}

void	fix_order(char **s, int *i)
{
	char	*tmp;
	char	*c;

	c = ft_itoa(*i);
	tmp = ft_strjoin(*s, c);
	if (*s)
		free(*s);
	*s = ft_strdup(tmp);
	free(tmp);
	free(c);
	(*i)++;
}
