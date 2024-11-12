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
	return (cmd);
}

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

static void	syntax_error(int check, t_cmd **head, t_info *info)
{
	if (check)
	{
		printf("syntax error near unexpected token\n");
		info->exit_code = 2;
		*head = NULL;
	}
}

t_cmd	*parse_tokens(t_token *tokens, t_info *info)
{
	t_cmd	*head;
	t_cmd	*cmd;
	t_cmd	*copy;

	cmd = NULL;
	head = NULL;
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
			if (tokens && tokens->type == WORD)
				add_cmd_arg(&(cmd->input), tokens->txt);
		}
		else if (tokens->type == OUTPUT)
		{
			syntax_error(tokens->next->type != WORD, &head, info);
			tokens = tokens->next;
			if (tokens && tokens->type == WORD)
				add_cmd_arg(&(cmd->output), tokens->txt);
		}
		else if (tokens->type == APPEND)
		{
			syntax_error(tokens->next->type != WORD, &head, info);
			tokens = tokens->next;
			if (tokens && tokens->type == WORD)
				add_cmd_arg(&(cmd->append), tokens->txt);

		}
		else if (tokens->type == HEREDOC)
		{
			syntax_error(tokens->next->type != WORD, &head, info);
			tokens = tokens->next;
			if (tokens && tokens->type == WORD)
				add_cmd_arg(&(cmd->delimiter), tokens->txt);
		}
		else if (tokens->type == PIPE)
		{
			syntax_error(tokens->next->type == DONE
				|| tokens->next->type == PIPE, &head, info);
			cmd->next = cmd_new();
			cmd->next->prev = cmd;
			cmd = cmd->next;
		}
		tokens = tokens->next;
	}
	if (head == NULL)
		free_command_list(copy);
	return (head);
}
