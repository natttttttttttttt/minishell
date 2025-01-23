/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vars_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pibouill <pibouill@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 14:11:15 by pibouill          #+#    #+#             */
/*   Updated: 2024/12/06 14:13:51 by pibouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static char	*handle_special_characters(const char *txt, int *i)
{
	if (txt[*i] == '\"' || txt[*i] == ' ' || txt[*i] == '?')
	{
		if (txt[*i] == '?')
		{
			(*i)++;
			return (ft_strdup("$?"));
		}
		(*i)++;
		return (ft_strdup("$"));
	}
	if (!txt[*i])
		return (ft_strdup("$"));
	return (NULL);
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
		return (handle_special_characters(txt, i));
	var = malloc(sizeof(char) * (*i - start + 1));
	if (!var)
		return (NULL);
	ft_strncpy(var, txt + start, *i - start);
	var[*i - start] = '\0';
	if (txt[*i] == '\"')
		(*i)++;
	return (var);
}

void	vars_to_value(t_token *lst, t_info info)
{
	char	*s;

	while (lst)
	{
		if (lst->type == VAR)
		{
			s = replace_env_vars(lst->txt, info, 0, 0);
			free(lst->txt);
			lst->txt = s;
			lst->type = WORD;
		}
		lst = lst->next;
	}
}
