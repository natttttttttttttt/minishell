#include "minishell.h"

void	ft_signal_handler(int signal)
{
	if (signal == SIGINT)
	{
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	sig_handl_child(int signal)
{
	if (signal == SIGINT)
	{
		exit(130);
	}
}

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

int	parsing_ok(char *str)
{
	if (!str)
		return (0);
	if (str[0] == '\0' || str[0] == '\n')
		return (0);
	if (all_spaces(str))
		return (0);
	return (1);
}


// void	print_cmd_lst(t_cmd *cmd_lst)
// {
// 	t_cmd	*cmd;
// 	int		i;

// 	cmd = cmd_lst;
// 	while (cmd)
// 	{
// 		i = 0;
// 		printf("Command:\n");
// 		while (cmd->args[i])
// 		{
// 			printf("  Arg[%d]: %s\n", i, cmd->args[i]);
// 			i++;
// 		}
// 		if (cmd->input)
// 			printf("  Input File: %s\n", cmd->input);
// 		i = 0;
// 		while (cmd->output[i])
// 		{
// 			printf("  Output File[%d]: %s\n", i, cmd->output[i]);
// 			i++;
// 		}
// 		if (cmd->append)
// 			printf("  Append File: %s\n", cmd->append);
// 		if (cmd->delimiter)
// 			printf("  Heredoc Delimiter: %s\n", cmd->delimiter);
// 		cmd = cmd->next;
// 		if (cmd)
// 			printf("  |\n");
// 	}
// }

void	info_init(t_info *info, char **envp)
{
	info->input = NULL;
	info->my_envp = copy_envp(envp);
	info->env_path = getenv("PATH");
	info->paths = ft_split(info->env_path, ':');
	info->exit_code = 0;
	info->tokens = NULL;
	info->cmds = NULL;
}

void	parse_and_exe(t_info *info, t_cmd *cmd_lst, t_token *token_lst)
{
	add_history(info->input);
	if (save_tokens(info->input, &token_lst, info))
	{
		info->tokens = token_lst;
		//print_list(token_lst);
		vars_to_value(token_lst, *info);
		cmd_lst = parse_tokens(token_lst, info);
		//print_cmd_lst(cmd_lst);
		info->cmds = cmd_lst;
		if (cmd_lst)
		{
			cmd_to_path(cmd_lst, info);
			execute_commands(cmd_lst, info);
			free_command_list(cmd_lst);
		}
		free_token_lst(token_lst);
	}
	free(info->input);
}

int	main(int argc, char **argv, char **envp)
{
	t_token	*token_lst;
	t_cmd	*cmd_lst;
	t_info	info;

	(void)argc;
	(void)argv;
	signal(SIGINT, ft_signal_handler);
	signal(SIGQUIT, SIG_IGN); // ignore Ctrl+backslash
	signal(SIGTSTP, SIG_IGN); // ignore Ctrl+Z (just in case)
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
		else if (parsing_ok(info.input))
		{
			cmd_lst = NULL;
			parse_and_exe(&info, cmd_lst, token_lst);
		}
	}
	free_arr(info.paths);
	free_arr(info.my_envp);
	return (0);
}
