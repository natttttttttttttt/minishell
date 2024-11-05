/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pibouill <pibouill@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 16:35:15 by pibouill          #+#    #+#             */
/*   Updated: 2024/11/05 17:06:26 by pibouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static char	*append_substr_norm(char *copy, const char *txt, int start, int end)
{
	char	*tmp;
	int		i;

	i = 0;
	if (ft_strchr(copy, '\"') && ft_strchr(copy, '\"') <= &txt[end])
	{
		tmp = malloc(sizeof(char) * (end - start));
		while (start + 1 <= end)
		{
			if (txt[start] == '\"')
				start++;
			else
				tmp[i++] = txt[start++];
		}
		tmp[i] = '\0';
	}
	else
	{
		tmp = malloc(sizeof(char) * (end - start + 1));
		ft_strncpy(tmp, txt + start, end - start);
	}
	return (tmp);
}

char	*extract_variable(const char *txt, int *i)
{
	int		start;
	char	*var;

	start = *i;
	if (!(txt[*i] >= '0' && txt[*i] <= '9'))
		while (txt[*i] && (ft_isalnum(txt[*i]) || txt[*i] == '_'))
			(*i)++;
	if (*i == start)
	{
		if (txt[*i] == '\"')
			return ((*i)++, ft_strdup("$"));
		if (txt[*i] == ' ')
			return ((*i)++, ft_strdup("$"));
		if (txt[*i] == '?')
			return ((*i)++, ft_strdup("$?"));
		if (!txt[*i])
			return (ft_strdup("$"));
		return (NULL);
	}
	var = malloc(sizeof(char) * (*i - start + 1));
	ft_strncpy(var, txt + start, *i - start);
	if (txt[*i] == '\"')
		(*i)++;
	return (var);
}

char	*append_substring(char *s, const char *txt, int start, int end)
{
	char	*tmp;
	char	*res;
	char	*copy;

	copy = ft_strdup(&txt[start]);
	tmp = append_substr_norm(copy, txt, start, end);
	res = ft_strjoin(s, tmp);
	free(s);
	free(tmp);
	free(copy);
	return (res);
}

char	*append_env_value(char *s, char **env_val, int f)
{
	char	*res;

	if (!(*env_val))
	{
		*env_val = ft_strdup("");
		f = 1;
	}
	if (s)
	{
		res = ft_strjoin(s, *env_val);
		free(s);
	}
	else
		res = ft_strdup(*env_val);
	if (f)
		free(*env_val);
	return (res);
}

void	vars_to_value(t_token *lst, t_info info)
{
	char	*s;

	while (lst)
	{
		if (lst->type == VAR)
		{
			if (lst->type != WORD)
			{
				s = replace_env_vars(lst->txt, info, 0, 0);
				free(lst->txt);
				lst->txt = s;
				lst->type = WORD;
			}
		}
		lst = lst->next;
	}
}
