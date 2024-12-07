/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pibouill <pibouill@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 13:39:51 by pibouill          #+#    #+#             */
/*   Updated: 2024/12/06 13:48:12 by pibouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//can norminette

void	add_cmd_arg(char ***arr, char *arg)
{
	char	**tmp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (*arr)
	{
		while ((*arr)[i])
			i++;
		tmp = (char **)malloc(sizeof(char *) * (i + 1));
		if (!tmp)
			return ;
		while (j < i)
		{
			tmp[j] = (*arr)[j];
			j++;
		}
		free(*arr);
		*arr = (char **)malloc(sizeof(char *) * (i + 2));
		if (!arr)
		{
			free(tmp);
			return ;
		}
		j = 0;
		while (j < i)
		{
			(*arr)[j] = tmp[j];
			j++;
		}
		(*arr)[i] = ft_strdup(arg);
		(*arr)[i + 1] = NULL;
		free(tmp);
	}
	else
	{
		(*arr) = (char **)malloc(sizeof(char *) * 2);
		if (!(*arr))
			return ;
		(*arr)[0] = ft_strdup(arg);
		(*arr)[1] = NULL;
	}
}

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

static void	syntax_error(int check, t_cmd **head, t_info *info)
{
	if (check)
	{
		printf("syntax error near unexpected token\n");
		info->exit_code = 2;
		*head = NULL;
	}
}

//until here or with this function if you just put every if separately, cause i will need space there

t_cmd	*parse_tokens(t_token *tokens, t_info *info)
{
	t_cmd	*head;
	t_cmd	*cmd;
	t_cmd	*copy;
	int		i;

	cmd = NULL;
	head = NULL;
	i = 0;
	if (tokens)
	{
		cmd = cmd_new();
		head = cmd;
		copy = cmd;
		syntax_error(tokens->type == PIPE, &head, info);
	}
	while (tokens)
	{
		if (tokens->type == WORD)
			add_cmd_arg(&(cmd->args), tokens->txt);
		else if (tokens->type == INPUT)
		{
			syntax_error(tokens->next->type != WORD, &head, info);
			tokens = tokens->next;
			if (!find_heredoc(tokens) || !cmd->delimiter)
			{
				if (tokens && tokens->type == WORD)
					add_cmd_arg(&(cmd->input), tokens->txt);
				fix_order(&cmd->order->input, &i);
			}
		}
		else if (tokens->type == OUTPUT)
		{
			syntax_error(tokens->next->type != WORD, &head, info);
			tokens = tokens->next;
			if (tokens && tokens->type == WORD)
				add_cmd_arg(&(cmd->output), tokens->txt);
			fix_order(&cmd->order->output, &i);
		}
		else if (tokens->type == APPEND)
		{
			syntax_error(tokens->next->type != WORD, &head, info);
			tokens = tokens->next;
			if (tokens && tokens->type == WORD)
				add_cmd_arg(&(cmd->append), tokens->txt);
			fix_order(&cmd->order->append, &i);
		}
		else if (tokens->type == HEREDOC)
		{
			syntax_error(tokens->next->type != WORD, &head, info);
			tokens = tokens->next;
			if (tokens && tokens->type == WORD)
				add_cmd_arg(&(cmd->delimiter), tokens->txt);
			if (!cmd->order->heredoc)
			{
				cmd->order->heredoc = ft_strdup(ft_itoa(i));
				i++;
			}
		}
		else if (tokens->type == PIPE)
		{
			cmd->order->count = i;
			i = 0;
			syntax_error(tokens->next->type == DONE
				|| tokens->next->type == PIPE, &head, info);
			cmd->next = cmd_new();
			cmd->next->prev = cmd;
			cmd = cmd->next;
		}
		tokens = tokens->next;
	}
	cmd->order->count = i;
	if (head == NULL)
		free_command_list(copy);
	return (head);
}
