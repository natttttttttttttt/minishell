/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pibouill <pibouill@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 16:19:45 by pibouill          #+#    #+#             */
/*   Updated: 2024/11/05 16:20:28 by pibouill         ###   ########.fr       */
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

void	free_command_list(t_cmd *head)
{
	t_cmd	*node;
	t_cmd	*next;

	node = head;
	while (node != NULL)
	{
		next = node->next;
		free_arr(node->args);
		free_arr(node->output);
		free(node->input);
		free_arr(node->append);
		free(node->delimiter);
		free(node);
		node = next;
	}
}

void	free_all(t_cmd *cmd, t_token *token)
{
	free_token_lst(token);
	free_command_list(cmd);
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
