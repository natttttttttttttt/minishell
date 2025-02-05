/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pibouill <pibouill@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 14:09:37 by pibouill          #+#    #+#             */
/*   Updated: 2025/02/05 15:44:24 by pibouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	quotes_err(t_info *info, char c)
{
	printf("unexpected EOF while looking for matching %c\n", c);
	info->exit_code = 2;
}

int	find_quotes(char *str, int *i, t_info *info)
{
	char	c;

	c = str[*i];
	if (c == '\'' || c == '\"')
	{
		(*i)++;
		while (str[*i] && str[*i] != c)
			(*i)++;
		if (str[*i] == '\0')
		{
			quotes_err(info, c);
			return (-1);
		}
	}
	return (0);
}

int	free_and_fail(t_token **lst)
{
	free_token_lst(*lst);
	return (0);
}

int	save_tokens(char *str, t_token **lst, t_info *info)
{
	int	i[2];

	i[0] = 0;
	i[1] = 0;
	while ((str[i[0]] > 8 && str[i[0]] < 14) || str[i[0]] == 32)
	{
		i[0]++;
		i[1]++;
	}
	while (str[i[0]])
	{
		if (find_quotes(str, &i[0], info) == -1)
			return (free_and_fail(lst));
		handle_separator(str, i, lst, info);
		i[0]++;
	}
	finalize_tokens(str, i, lst, info);
	return (1);
}
