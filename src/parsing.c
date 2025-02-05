/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pibouill <pibouill@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 14:09:37 by pibouill          #+#    #+#             */
/*   Updated: 2025/01/28 12:00:04 by pibouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*mixed_quotes(char *s)
{
	char	*res;
	int		i;
	int		j;
	int		v;

	i = 0;
	j = 0;
	v = 0;
	res = malloc(ft_strlen(s) + 1);
	while (s[i])
	{
		while (s[i] != '\'' && s[i] != '\"')
			res[j++] = s[i++];
		if  (s[i] == '\"')
		{
			i++;
			while (s[i] != '\"')
			{
				if (s[i] == '$')
					v = 1;
				res[j++] = s[i++];
			}
			if (v)
				res[j++] = s[i++];
			else
				i++;
			v = 0;
		}
		if  (s[i] == '\'')
		{
			i++;
			while (s[i] != '\'')
				res[j++] = s[i++];
			i++;
		}
	}
	res[j] = '\0';
	return (res);
}

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
