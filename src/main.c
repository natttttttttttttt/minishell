/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pibouill <pibouill@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 16:21:11 by pibouill          #+#    #+#             */
/*   Updated: 2024/11/15 17:47:17 by pibouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include <readline/readline.h>
#include <signal.h>

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

bool	set_signal = false;

void	handle_sigint()
{
	set_signal = true;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

// gonna have to this somewhere (not sure where for now hehe)
void	restore_sigint_in_child(struct sigaction sigint)
{
	if (set_signal == true)
		sigaction(SIGINT, &sigint, NULL);
}
/*
 * So I finally got the answer.
 * The thing is that when the process was forked (let's say we ran
 * `/usr/bin/cat`) and then interrupted with `SIGINT` the wait called
 * failed and the parent was unwaited for (thus creating a zombie and
 * messing will all the other wait calls). If we ran after that command,
 * a command such as `/usr/bin/ls` the process encountered the previous
 * zombie that had been unwaited for, returned early, printed the prompt
 * and only after the ls command printed its output.
 * The solution is to set `sa.sa_flags = SA_SIGINFO | SA_RESTART` (in
 * function `init_sig`) so that the wait call will be restarted when
 * `SIGINT` is received.
 */

int	main(int argc, char **argv, char **envp)
{
	t_token	*token_lst;
	t_cmd	*cmd_lst;
	t_info	info;
	struct sigaction	sigint;
	struct sigaction	sigstop;
	struct sigaction	sigquit;

	(void)argc;
	(void)argv;
	info_init(&info, envp);
	sigint.sa_handler = handle_sigint;
	sigint.sa_flags = SA_SIGINFO | SA_RESTART;
	sigstop.sa_handler = SIG_IGN;
	sigquit.sa_handler = SIG_IGN;
	sigemptyset(&sigint.sa_mask);
	sigemptyset(&sigquit.sa_mask);
	sigemptyset(&sigstop.sa_mask);
	sigaction(SIGINT, &sigint, NULL);
	sigaction(SIGTSTP, &sigstop, NULL);
	sigaction(SIGQUIT, &sigquit, NULL);
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
