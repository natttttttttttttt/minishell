#include "minishell.h"

t_cmd	*cmd_new(void)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	cmd->args = NULL;
	cmd->input = NULL;
	cmd->output = NULL;
	cmd->append = NULL;
	cmd->delimiter = NULL;
	cmd->next = NULL;
	cmd->prev = NULL;
	cmd->builtin = 0;
	return (cmd);
}



void	add_cmd_arg(t_cmd *cmd, char *arg)
{
	char	**tmp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (cmd->args)
	{
		while (cmd->args[i])
			i++;
		tmp = (char **)malloc(sizeof(char *) * (i + 1));
		if (!tmp)
			return ;
		while (j < i)
		{
			tmp[j] = cmd->args[j];
			j++;
		}
		free(cmd->args);
		cmd->args = (char **)malloc(sizeof(char *) * (i + 2));
		if (!cmd->args)
		{
			free(tmp);
			return ;
		}
		j = 0;
		while (j < i)
		{
			cmd->args[j] = tmp[j];
			j++;
		}
		cmd->args[i] = ft_strdup(arg);
		cmd->args[i + 1] = NULL;
		free(tmp);
	}
	else
	{
		cmd->args = (char **)malloc(sizeof(char *) * 2);
		if (!cmd->args)
			return ;
		cmd->args[0] = ft_strdup(arg);
		cmd->args[1] = NULL;
	}
}

t_cmd	*parse_tokens(t_token *tokens)
{
	t_cmd	*head;
	t_cmd	*cmd;

	cmd = NULL;
	head = NULL;
	if (tokens)
	{
		if (tokens->type == PIPE)
		{
			printf("syntax error near unexpected token |\n");
			return (NULL);
		}
		cmd = cmd_new();
		head = cmd;
	}
	while (tokens)
	{
		if (tokens->type == WORD)
			add_cmd_arg(cmd, tokens->txt);
		else if (tokens->type == INPUT)
		{
			if (tokens->next->type != WORD)
			{
				printf("syntax error near unexpected token\n");
				return (NULL);
			}
			tokens = tokens->next;
			if (tokens && tokens->type == WORD)
				cmd->input = ft_strdup(tokens->txt);
		}
		else if (tokens->type == OUTPUT)
		{
			if (tokens->next->type != WORD)
			{
				printf("syntax error near unexpected token\n");
				return (NULL);
			}
			tokens = tokens->next;
			if (tokens && tokens->type == WORD)
				cmd->output = ft_strdup(tokens->txt);
		}
		else if (tokens->type == APPEND)
		{
			if (tokens->next->type != WORD)
			{
				printf("syntax error near unexpected token\n");
				return (NULL);
			}
			tokens = tokens->next;
			if (tokens && tokens->type == WORD)
				cmd->append = ft_strdup(tokens->txt);

		}
		else if (tokens->type == HEREDOC)
		{
			if (tokens->next->type != WORD)
			{
				printf("syntax error near unexpected token\n");
				return (NULL);
			}
			tokens = tokens->next;
			if (tokens && tokens->type == WORD)
				cmd->delimiter = ft_strdup(tokens->txt);
		}
		else if (tokens->type == PIPE)
		{
			if (tokens->next->type == DONE || tokens->next->type == PIPE)
			{
				printf("syntax error near unexpected token\n");
				return (NULL);
			}
			cmd->next = cmd_new();
			cmd->next->prev = cmd;
			cmd = cmd->next;
		}
		tokens = tokens->next;
	}
	return (head);
}
