/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pibouill <pibouill@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 14:09:37 by pibouill          #+#    #+#             */
/*   Updated: 2024/12/06 14:10:05 by pibouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*deal_with_quotes(char *s, int q, int i)
{
	char	*res;
	int		l;
	int		j;

	l = ft_strlen(s);
	if (q == 1 || (q == 2 && !(ft_strchr(s, '$'))))
		l = l - 2;
	else if (q == 2 && ft_strchr(s, '$'))
		l--;
	res = malloc(l + 1);
	if (!res)
		return (NULL);
	j = 0;
	while (s[i])
	{
		if ((q == 1 && s[i] == '\'')
			|| ((q == 2 && s[i] == '\"') && (ft_strchr(s, '$') > &s[i]))
			|| (q == 2 && (((ft_strchr(s, '$'))
						&& (ft_strchr(s, '\"') == &s[i]))
					|| (!(ft_strchr(s, '$')) && s[i] == '\"'))))
			i++;
		else
			res[j++] = s[i++];
	}
	res[j] = '\0';
	return (res);
}

void	quotes_err(int *quotes, t_info *info)
{
	printf("unexpected EOF while looking for matching \'\n");
	info->exit_code = 2;
	*quotes = -1;
}

void	find_quotes(char *str, int *i, int *quotes, t_info *info)
{
	if (str[*i] == '\'')
	{
		(*i)++;
		while (str[*i] && str[*i] != '\'')
			(*i)++;
		if (str[*i] != '\0')
			*quotes = 1;
		else
			quotes_err(quotes, info);
	}
	else if (str[*i] == '\"')
	{
		(*i)++;
		while (str[*i] && str[*i] != '\"')
			(*i)++;
		if (str[*i] != '\0')
			*quotes = 2;
		else
			quotes_err(quotes, info);
	}
}

int	free_and_fail(t_token **lst)
{
	free_token_lst(*lst);
	return (0);
}

int	save_tokens(char *str, t_token **lst, t_info *info)
{
	int	i[2];
	int	quotes;

	i[0] = 0;
	i[1] = 0;
	quotes = 0;
	while ((str[i[0]] > 8 && str[i[0]] < 14) || str[i[0]] == 32)
	{
		i[0]++;
		i[1]++;
	}
	while (str[i[0]])
	{
		find_quotes(str, &i[0], &quotes, info);
		if (quotes == -1)
			return (free_and_fail(lst));
		handle_separator(str, i, &quotes, lst);
		i[0]++;
	}
	finalize_tokens(str, i, quotes, lst);
	return (1);
}
