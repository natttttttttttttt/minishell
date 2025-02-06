/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pibouill <pibouill@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 11:58:10 by pibouill          #+#    #+#             */
/*   Updated: 2025/02/05 16:45:17 by pibouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*get_env_var(char *s, int *i, t_info *info, char **buf)
{
	char	*var;
	char	*env;

	var = NULL;
	env = NULL;
	if (s[*i] && s[*i] == '?')
	{
		env = ft_itoa(info->exit_code);
		(*i)++;
	}
	else if (s[*i] && !ft_isdigit(s[*i]))
	{
		while (ft_isalnum(s[*i]) || s[*i] == '_')
			add_buf(&var, s[(*i)++]);
		if (var)
		{
			env = ft_strdup(ft_getenv(info->my_envp, var));
			free(var);
		}
	}
	else
		add_buf(buf, '$');
	return (env);
}

void	add_var(int *i, char *s, t_info *info, char **buf)
{
	char	*env;
	int		j;

	env = get_env_var(s, i, info, buf);
	j = 0;
	while (env && env[j])
		add_buf(buf, env[j++]);
	if (env)
		free(env);
}

char	*handle_quotes(char *s, int *i, int *q)
{
	while ((s[*i] == '\'' && *q != 2) || (s[*i] == '\"' && *q != 1))
	{
		*q = q_mode(*q, s[*i]);
		(*i)++;
	}
	return (s);
}

char	*deal_with_quotes(char *s, t_info *info)
{
	char	*buf;
	int		i;
	int		q;

	buf = ft_strdup("");
	q = 0;
	i = 0;
	while (s[i])
	{
		handle_quotes(s, &i, &q);
		if (s[i] && s[i] == '$' && q != 1)
		{
			i++;
			add_var(&i, s, info, &buf);
		}
		else if (s[i])
		{
			add_buf(&buf, s[i]);
			i++;
		}
	}
	return (buf);
}
