/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pibouill <pibouill@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 16:40:40 by pibouill          #+#    #+#             */
/*   Updated: 2025/01/14 13:38:54 by pibouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#define PROMPT "\033[0;35mminishell\033[1;36m> \033[0m"

int	g_sigflag = 0;

static void	info_init(t_info *info, char **envp)
{
	g_sigflag = 0;
	info->input = NULL;
	info->my_envp = copy_envp(envp);
	info->env_path = NULL;
	info->paths = NULL;
	info->exit_code = 0;
	info->err = 0;
	info->tokens = NULL;
	info->cmds = NULL;
	info->status = 0;
}

static void	cleanup_info(t_info *info)
{
	if (info->paths)
		free_arr(info->paths);
	if (info->my_envp)
		free_arr(info->my_envp);
}

static void	parse_and_exe(t_info *info, t_cmd *cmd_lst, t_token *token_lst)
{
	add_history(info->input);
	if (save_tokens(info->input, &token_lst, info))
	{
		info->tokens = token_lst;
		cmd_lst = parse_tokens(token_lst, info);
		info->cmds = cmd_lst;
		if (cmd_lst)
		{
			cmd_to_path(cmd_lst, info);
			execute_commands(cmd_lst, info);
			free_command_list(&cmd_lst);
		}
		free_token_lst(token_lst);
	}
	free(info->input);
}

static int	flag_and_input_check(t_info *info)
{
	if (g_sigflag != 0)
	{
		info->exit_code = 130;
		g_sigflag = 0;
		return (0);
	}
	if (!info->input)
	{
		printf("exit\n");
		return (1);
	}
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_token	*token_lst;
	t_cmd	*cmd_lst;
	t_info	info;

	(void)argc;
	(void)argv;
	token_lst = NULL;
	cmd_lst = NULL;
	info_init(&info, envp);
	setup_signals();
	while (1)
	{
		info.input = readline(PROMPT);
		if (!info.input)
		{
			write(1, "exit\n", 5);
			break ;
		}
		if (1 == flag_and_input_check(&info))
			break ;
		if (parsing_ok(info.input))
			parse_and_exe(&info, cmd_lst, token_lst);
	}
	cleanup_info(&info);
	return (0);
}
