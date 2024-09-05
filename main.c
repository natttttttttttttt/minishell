#include "minishell.h"

int	all_spaces(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if ((str[i] > 8 && str[i] < 14) || str[i] == 32)
			i++;
		else
			return (0);
	}
	return (1);
}

int	parsing(char *str)
{
	if (!str)
		return (0);
	if (str[0] == '\0' || str[0] == '\n')
		return (0);
	if (all_spaces(str))
		return (0);
	return (1);
}

void	substitute_vars(t_token *lst, int i, int start)
{
	char	*s;
	char	*v;
	char	*tmp;
	char	*env_val;

	while (lst)
	{
		if (lst->type == VAR)
		{
			s = ft_strdup("");
			i = 0;
			start = 0;
			while ((lst->txt)[i])
			{
				if ((lst->txt)[i] == '$')
				{
					if (i != start)
					{
						tmp = s;
						s = ft_strjoin(s, ft_strabcpy(lst->txt, start, i - 1));
						free(tmp);
					}
					start = i + 1;
					i++;
					while ((lst->txt)[i] && (ft_isalnum((lst->txt)[i]) || (lst->txt)[i] == '_'))
						i++;
					v = ft_strabcpy((lst->txt), start, i - 1);
					env_val = getenv(v);
					free(v);
					if (env_val)
					{
						tmp = s;
						s = ft_strjoin(s, env_val);
						free(tmp);
					}
					else
						printf("var not found\n");
					start = i;
				}
				i++;
			}
			tmp = s;
			s = ft_strjoin(s, ft_strabcpy(lst->txt, start, i - 1));
			free(tmp);
			free(lst->txt);
			lst->txt = ft_strdup(s);
			free(s);
		}
		lst = lst->next;
	}
}

#include <stdio.h>

void print_cmd_lst(t_cmd *cmd_lst) {
    t_cmd *current_cmd = cmd_lst;

    while (current_cmd) {
        // Print the command and its arguments
        printf("Command:\n");
        if (current_cmd->args) {
            for (int i = 0; current_cmd->args[i]; i++) {
                printf("  Arg[%d]: %s\n", i, current_cmd->args[i]);
            }
        }

        // Print input redirection
        if (current_cmd->input) {
            printf("  Input File: %s\n", current_cmd->input);
        }

        // Print output redirection
        if (current_cmd->output) {
            printf("  Output File: %s\n", current_cmd->output);
        }

        // Print append redirection
        if (current_cmd->append) {
            printf("  Append File: %s\n", current_cmd->append);
        }

        // Print heredoc delimiter
        if (current_cmd->delimiter) {
            printf("  Heredoc Delimiter: %s\n", current_cmd->delimiter);
        }

        // Move to the next command in the pipeline
        current_cmd = current_cmd->next;
        
        // Print a separator if there is another command in the pipeline
        if (current_cmd) {
            printf("  |\n");
        }
    }
}

void data_init(t_data *data)
{
	data->pipes = 0;
	data->env_path = getenv("PATH");
	data->paths = ft_split(data->env_path, ':');
}
int	main(int argc, char **argv, char **envp)
{
	t_token	*token_lst;
	t_cmd	*cmd_lst;
	t_data	data;
	

	data_init(&data);
	
	
	while (1)
	{
		token_lst = NULL;
		data.input = readline("minishell> ");
		if (parsing(data.input))
			save_tokens(data.input, &token_lst);
		substitute_vars(token_lst, 0, 0);
		//print_list(token_lst);
		cmd_lst = parse_tokens(token_lst, &data);
		cmd_to_path(cmd_lst, data);
		print_cmd_lst(cmd_lst);
		if (data.pipes == 0)
			if (execve(cmd_lst->args[0], cmd_lst->args, envp) == -1) {
    perror("execve failed");
}
		free(data.input);
		free_lst(&token_lst);
	}
	return (0);
}