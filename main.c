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

void	substitute_vars(t_token *lst, int i, int start, t_info info)
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
					env_val = ft_getenv(info.my_envp, v);
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
			lst->type = WORD;
		}
		lst = lst->next;
	}
}



void print_cmd_lst(t_cmd *cmd_lst) {
    t_cmd *cmd = cmd_lst;

    while (cmd) {
        // Print the command and its arguments
        printf("Command:\n");
        if (cmd->args) {
            for (int i = 0; cmd->args[i]; i++) {
                printf("  Arg[%d]: %s\n", i, cmd->args[i]);
            }
        }

        // Print input redirection
        if (cmd->input) {
            printf("  Input File: %s\n", cmd->input);
        }

        // Print output redirection
        if (cmd->output) {
            printf("  Output File: %s\n", cmd->output);
        }

        // Print append redirection
        if (cmd->append) {
            printf("  Append File: %s\n", cmd->append);
        }

        // Print heredoc delimiter
        if (cmd->delimiter) {
            printf("  Heredoc Delimiter: %s\n", cmd->delimiter);
        }

        // Move to the next command in the pipeline
        cmd = cmd->next;
        
        // Print a separator if there is another command in the pipeline
        if (cmd) {
            printf("  |\n");
        }
    }
}

void info_init(t_info *info, char **envp)
{
	info->my_envp = copy_envp(envp);
	info->env_path = getenv("PATH");
	info->paths = ft_split(info->env_path, ':');
}

int	main(int argc, char **argv, char **envp)
{
	t_token	*token_lst;
	t_cmd	*cmd_lst;
	t_info	info;
	(void)argc;
	(void)argv;

	info_init(&info, envp);
	while (1)
	{
		token_lst = NULL;
		info.input = readline("minishell> ");
		if (!info.input) {
            printf("exit\n");
            break;
        }
		else if (parsing(info.input))
		{
			add_history(info.input);
			save_tokens(info.input, &token_lst);
			substitute_vars(token_lst, 0, 0, info);
			//print_list(token_lst);
			cmd_lst = parse_tokens(token_lst);
			cmd_to_path(cmd_lst, info);
			//print_cmd_lst(cmd_lst);
			execute_commands(cmd_lst, info);
			free(info.input);
			free_token_lst(token_lst);
			free_command_list(cmd_lst);
		}
	}	
	free_arr(info.paths);
	return (0);
}