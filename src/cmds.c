/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pibouill <pibouill@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 13:39:51 by pibouill          #+#    #+#             */
/*   Updated: 2025/01/08 16:45:44 by pibouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//can norminette

void	print_order(t_order *order)
{
	if (order == NULL)
	{
		printf("Order is NULL\n");
		return ;
	}
	printf("Order details:\n");
	// Print the strings (using NULL check)
	printf("Input: %s\n", (order->input) ? order->input : "NULL");
	printf("Output: %s\n", (order->output) ? order->output : "NULL");
	printf("Append: %s\n", (order->append) ? order->append : "NULL");
	printf("Heredoc: %s\n", (order->heredoc) ? order->heredoc : "NULL");
	// Print the integers
	printf("Input index: %d\n", order->i_input);
	printf("Output index: %d\n", order->i_output);
	printf("Append index: %d\n", order->i_append);
	printf("Count: %d\n", order->count);
}

static void	syntax_error(int check, t_info *info)
{
	if (check)
	{
		printf("syntax error near unexpected token\n");
		info->exit_code = 2;
		info->err = 1;
	}
}

void	tkn_input(t_token **tokens, t_info *info, t_cmd **cmd, int *i)
{
	syntax_error((*tokens)->next->type != WORD, info);
	(*tokens) = (*tokens)->next;
	if (!find_heredoc(*tokens) || !(*cmd)->delimiter)
	{
		if ((*tokens) && (*tokens)->type == WORD)
			add_cmd_arg(&((*cmd)->input), (*tokens)->txt);
		fix_order(&((*cmd)->order->input), i);
	}
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
		(*cmd)->order->heredoc = ft_strdup(ft_itoa(*i));
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

void	check_tkn(t_token **tokens, t_info *info, t_cmd **cmd, int *i)
{
	if ((*tokens)->type == WORD)
		add_cmd_arg(&((*cmd)->args), (*tokens)->txt);
	else if ((*tokens)->type == INPUT)
		tkn_input(tokens, info, cmd, i);
	else if ((*tokens)->type == OUTPUT)
		tkn_output(tokens, info, cmd, i);
	else if ((*tokens)->type == APPEND)
		tkn_append(tokens, info, cmd, i);
	else if ((*tokens)->type == HEREDOC)
		tkn_heredoc(tokens, info, cmd, i);
	else if ((*tokens)->type == PIPE)
		tkn_pipe(tokens, info, cmd, i);
}

t_cmd	*parse_tokens(t_token *tokens, t_info *info)
{
	t_cmd	*head;
	t_cmd	*cmd;
	int		i;

	cmd = NULL;
	head = NULL;
	i = 0;
	if (tokens)
	{
		cmd = cmd_new();
		head = cmd;
		syntax_error(tokens->type == PIPE, info);
	}
	while (tokens)
	{
		check_tkn(&tokens, info, &cmd, &i);
		tokens = tokens->next;
	}
	cmd->order->count = i;
	if (info->err)
		free_command_list(&head);
	return (head);
}
