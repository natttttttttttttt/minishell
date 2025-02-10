/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_to_path_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pibouill <pibouill@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 15:39:56 by pibouill          #+#    #+#             */
/*   Updated: 2025/02/05 15:44:10 by pibouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	possible(t_cmd *cmd_lst, t_info *info)
{
	char	*tmp;

	tmp = NULL;
	tmp = cmd_lst->args[0];
	cmd_lst->args[0] = get_cmd(info, tmp);
	free(tmp);
}

void	handle_empty_args(t_cmd *cmd_lst)
{
	if (!cmd_lst->args)
		add_cmd_arg(&(cmd_lst->args), "\0");
	if (cmd_lst->args[0][0] == '\0' && cmd_lst->args[1])
		del_arg(cmd_lst->args);
}

static void	cmd_not_found(t_cmd *cmd_lst, t_info *info)
{
	printf("%s: command not found\n", cmd_lst->args[0]);
	info->exit_code = 127;
	free(cmd_lst->args[0]);
	cmd_lst->args[0] = ft_strdup("");
}

void	handle_path_checks(t_cmd *cmd_lst, t_info *info)
{
	if ((access(cmd_lst->args[0], F_OK) == 0)
		&& !(ft_strchr(cmd_lst->args[0], '/')))
		cmd_not_found(cmd_lst, info);
	else if (access(cmd_lst->args[0], X_OK) != 0)
		possible(cmd_lst, info);
}
