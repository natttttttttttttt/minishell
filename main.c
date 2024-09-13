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
			if (ft_strncmp(lst->txt, "$?", 2) == 0)
			{
				
				free(lst->txt);
				lst->txt = ft_itoa(info.exit_code);
				lst->type = WORD;
				lst = lst->next;
				continue ;
			}
			s = ft_strdup("");
			i = 0;
			start = 0;
			while ((lst->txt)[i])
			{
				if ((lst->txt)[i] == '$')
				{
					if (i != start)
					{
						tmp = malloc(sizeof(char) * (i - start + 1));;
						ft_strncpy(tmp, lst->txt + start, i - start);
						s = ft_strjoin(s, tmp);
						free(tmp);
					}
					start = ++i;
					while ((lst->txt)[i] && (ft_isalnum((lst->txt)[i])
							|| (lst->txt)[i] == '_'))
						i++;
					v = malloc(sizeof(char) * (i - start + 1));
					ft_strncpy(v, lst->txt + start, i - start);
					env_val = ft_getenv(info.my_envp, v);
					free(v);
					tmp = s;
					if (env_val)
						s = ft_strjoin(tmp, env_val);
					free(tmp);
					start = i;
				}
				else
					i++;
			}
			if (i != start)
			{
				tmp = malloc(sizeof(char) * (i - start + 1));
				ft_strncpy(tmp, lst->txt + start, i - start);
				s = ft_strjoin(s, tmp);
				free(tmp);
			}
			free(lst->txt);
			if (!env_val)
				lst->txt = ft_strdup("");
			else
				lst->txt = ft_strdup(s);
			free(s);
			lst->type = WORD;
		}
		lst = lst->next;
	}
}




void	print_cmd_lst(t_cmd *cmd_lst)
{
	t_cmd	*cmd;
	int		i;

	cmd = cmd_lst;
	i = 0;
	while (cmd)
	{
		printf("Command:\n");
		while (cmd->args[i])
		{
			printf("  Arg[%d]: %s\n", i, cmd->args[i]);
			i++;
		}
		if (cmd->input)
			printf("  Input File: %s\n", cmd->input);
		if (cmd->output)
			printf("  Output File: %s\n", cmd->output);
		if (cmd->append)
			printf("  Append File: %s\n", cmd->append);
		if (cmd->delimiter)
			printf("  Heredoc Delimiter: %s\n", cmd->delimiter);
		cmd = cmd->next;
		if (cmd)
			printf("  |\n");
	}
}

void	info_init(t_info *info, char **envp)
{
	info->input = NULL;
	info->my_envp = copy_envp(envp);
	info->env_path = getenv("PATH");
	info->paths = ft_split(info->env_path, ':');
	info->exit_code = 0;
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
		if (!info.input)
		{
			printf("exit\n");
			break ;
		}
		else if (parsing(info.input))
		{
			add_history(info.input);
			if (save_tokens(info.input, &token_lst, &info))
			{
				substitute_vars(token_lst, 0, 0, info);
				print_list(token_lst);
				cmd_lst = parse_tokens(token_lst);
				cmd_to_path(cmd_lst, info);
				print_cmd_lst(cmd_lst);
				execute_commands(cmd_lst, &info);
				free(info.input);
				free_command_list(cmd_lst);
			}
			free_token_lst(token_lst);
		}
	}
	free_arr(info.paths);
	free_arr(info.my_envp);
	return (0);
}
