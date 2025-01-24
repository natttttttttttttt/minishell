/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pibouill <pibouill@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 13:32:01 by pibouill          #+#    #+#             */
/*   Updated: 2025/01/14 13:35:36 by pibouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	tkn_input(t_token **tokens, t_info *info, t_cmd **cmd, int *i)
{
	syntax_error((*tokens)->next->type != WORD, info);
	(*tokens) = (*tokens)->next;
	if ((*tokens) && (*tokens)->type == WORD)
		add_cmd_arg(&((*cmd)->input), (*tokens)->txt);
	fix_order(&((*cmd)->order->input), i);
}

void	tkn_output(t_token **tokens, t_info *info, t_cmd **cmd, int *i)
{
	syntax_error((*tokens)->next->type != WORD, info);
	(*tokens) = (*tokens)->next;
	if ((*tokens) && (*tokens)->type == WORD)
		add_cmd_arg(&((*cmd)->output), (*tokens)->txt);
	fix_order(&((*cmd)->order->output), i);
}

void	tkn_append(t_token **tokens, t_info *info, t_cmd **cmd, int *i)
{
	syntax_error((*tokens)->next->type != WORD, info);
	(*tokens) = (*tokens)->next;
	if ((*tokens) && (*tokens)->type == WORD)
		add_cmd_arg(&((*cmd)->append), (*tokens)->txt);
	fix_order(&((*cmd)->order->append), i);
}

void	tkn_heredoc(t_token **tokens, t_info *info, t_cmd **cmd, int *i)
{
	syntax_error((*tokens)->next->type != WORD, info);
	(*tokens) = (*tokens)->next;
	if (*tokens && (*tokens)->type == WORD)
		add_cmd_arg(&((*cmd)->delimiter), (*tokens)->txt);
	if (!(*cmd)->order->heredoc)
	{
		(*cmd)->order->heredoc = ft_itoa(*i);
		(*i)++;
	}
}

void	tkn_pipe(t_token **tokens, t_info *info, t_cmd **cmd, int *i)
{
	(*cmd)->order->count = *i;
	*i = 0;
	syntax_error((*tokens)->next->type == DONE
		|| (*tokens)->next->type == PIPE, info);
	(*cmd)->next = cmd_new();
	(*cmd)->next->prev = *cmd;
	*cmd = (*cmd)->next;
}
