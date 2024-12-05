/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pibouill <pibouill@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 16:40:40 by pibouill          #+#    #+#             */
/*   Updated: 2024/11/24 11:14:36 by pibouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include <signal.h>
#include <unistd.h>

int	sigflag;

void	setup_signals(void)
{
	struct sigaction	sa;

	sa.sa_handler = ft_signal_handler;
	sa.sa_flags = SA_RESTART;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGINT, &sa, NULL);
}

void	sig_handl_child(int signal)
{
	if (signal == SIGINT)
	{
		exit(130);
	}
}

void	ft_signal_handler(int signal)
{
	sigflag = signal;
	if (signal == SIGINT)
	{
		//sig_handl_child(signal);
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
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

void print_string_array(char **arr)
{
    if (arr == NULL) {
        printf("NULL\n");
        return;
    }
    for (int i = 0; arr[i] != NULL; i++) {
        printf("%s ", arr[i]);
    }
    printf("\n");
}

// Function to print the contents of a t_cmd structure
void print_command(t_cmd *cmd)
{
    if (cmd == NULL) {
        printf("Command is NULL\n");
        return;
    }

    printf("Command:\n");
    
    // Print arguments
    printf("  args: ");
    print_string_array(cmd->args);

    // Print input redirection
    printf("  input: ");
    print_string_array(cmd->input);

    // Print output redirection
    printf("  output: ");
    print_string_array(cmd->output);

    // Print append redirection
    printf("  append: ");
    print_string_array(cmd->append);

    // Print delimiter
    printf("  delimiter: ");
    print_string_array(cmd->delimiter);

}

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
	info->tokens = token_lst;
	if (save_tokens(info->input, &token_lst, info))
	{
		//print_list(token_lst);
		vars_to_value(token_lst, *info);
		cmd_lst = parse_tokens(token_lst, info);
		//print_command(cmd_lst);
		info->cmds = cmd_lst;
		if (cmd_lst)
		{
			cmd_to_path(cmd_lst, info);
			execute_commands(cmd_lst, info, 0, 0);
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
	sigflag = 0;
	signal(SIGINT, ft_signal_handler);
	signal(SIGQUIT, SIG_IGN); // ignore Ctrl+backslash
	signal(SIGTSTP, SIG_IGN); // ignore Ctrl+Z (just in case)
	info_init(&info, envp);
	while (1)
	{
		token_lst = NULL;
		info.input = readline("\033[0;35mminishell\033[1;36m> \033[0m");
		if (sigflag != 0)
		{
			info.exit_code = 130;
			sigflag = 0;
		}
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
