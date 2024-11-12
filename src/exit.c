/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pibouill <pibouill@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 14:47:47 by pibouill          #+#    #+#             */
/*   Updated: 2024/11/12 14:48:31 by pibouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	free_before_exit(t_info *info)
{
	free_command_list(info->cmds);
	free_token_lst(info->tokens);
	free(info->input);
	free_arr(info->paths);
	free_arr(info->my_envp);
}

void	exit_builtin(char **args, t_info *info)
{
	int	code;

	code = 0;
	if (args[1] != NULL)
	{
		if (args[2] != NULL)
		{
			printf("exit: too many arguments\n");
			free_before_exit(info);
			exit (1);
		}
		if (all_digits(args[1]))
			code = ft_atoi(args[1]);
		else
		{
			printf("exit\n");
			printf("exit: %s: numeric argument required\n", args[1]);
			free_before_exit(info);
			exit (2);
		}
	}
	printf("exit\n");
	free_before_exit(info);
	exit(code);
}
