/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pibouill <pibouill@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 13:39:51 by pibouill          #+#    #+#             */
/*   Updated: 2025/01/14 13:36:13 by pibouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	syntax_error(int check, t_info *info)
{
	if (check)
	{
		if (info->err == 0)
			printf("syntax error near unexpected token\n");
		info->exit_code = 2;
		info->err = 1;
	}
}

void	check_tkn(t_token **tokens, t_info *info, t_cmd **cmd, int *i)
{
	if ((*tokens) == NULL)
		return ;
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

static t_cmd	*do_cmd_new(t_token *tokens, t_cmd **cmd, t_info *info)
{
	t_cmd	*head;

	head = NULL;
	*cmd = cmd_new();
	head = *cmd;
	if (tokens->type == PIPE)
	{
		syntax_error(1, info);
		return (NULL);
	}
	return (head);
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
		head = do_cmd_new(tokens, &cmd, info);
	while (tokens)
	{
		check_tkn(&tokens, info, &cmd, &i);
		if (info->err)
		{
			free_command_list(&head);
			info->err = 0;
			break ;
		}
		tokens = tokens->next;
	}
	if (head)
		return (cmd->order->count = i, head);
	else
		return (NULL);
}
