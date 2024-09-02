#include "minishell.h"

t_cmd *cmd_new()
{
    t_cmd *cmd = malloc(sizeof(t_cmd));
    cmd->args = NULL;
    cmd->input = NULL;
    cmd->output = NULL;
    cmd->append = NULL;
    cmd->delimiter = NULL;
    cmd->next = NULL;
    return cmd;
}

void add_cmd_arg(t_cmd *cmd, char *arg)
{
    int count = 0;
    if (cmd->args)
        while (cmd->args[count])
			count++;
    cmd->args = realloc(cmd->args, sizeof(char *) * (count + 2));
    cmd->args[count] = ft_strdup(arg);
    cmd->args[count + 1] = NULL;
}

t_cmd *parse_tokens(t_token *tokens) 
{
	t_cmd	*head;
	t_cmd	*current_cmd;
	int		arg_count;

	arg_count = 0;
	current_cmd = NULL;
	head = NULL;
	while (tokens)
	{
		if (!current_cmd)
			{
				current_cmd = cmd_new();
				if (!head)
					head = current_cmd;
			}
		if (tokens->type == WORD)
		{
			
			add_cmd_arg(current_cmd, tokens->txt);
			arg_count++;
		}
		else if (tokens->type == INPUT)
		{
			tokens = tokens->next;
			if (tokens && tokens->type == WORD)
				current_cmd->input = ft_strdup(tokens->txt);
		}
		else if (tokens->type == OUTPUT)
		{
			tokens = tokens->next;
			if (tokens && tokens->type == WORD)
				current_cmd->output = ft_strdup(tokens->txt);
		}
		else if (tokens->type == APPEND)
		{
			tokens = tokens->next;
			if (tokens && tokens->type == WORD)
				current_cmd->append = ft_strdup(tokens->txt);

		}
		else if (tokens->type == HEREDOC)
		{
			tokens = tokens->next;
			if (tokens && tokens->type == WORD)
				current_cmd->delimiter = ft_strdup(tokens->txt);
		}
		else if (tokens->type == PIPE)
		{
			if (current_cmd)
			{
				current_cmd->next = cmd_new();
				current_cmd = current_cmd->next;
			}
		}
		tokens = tokens->next;
	}
	return (head);
}