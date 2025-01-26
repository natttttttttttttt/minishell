/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pibouill <pibouill@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 14:10:41 by pibouill          #+#    #+#             */
/*   Updated: 2024/12/06 14:13:46 by pibouill         ###   ########.fr       */
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
		if (!tmp)
			return (NULL);
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
		if (!tmp)
			return (NULL);
		ft_strncpy(tmp, txt + start, end - start);
	}
	return (tmp);
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

static void	replace_env_norm(char *var, t_info info, char **s)
{
	char	*env_val;
	int		f;

	f = 1;
	if (var)
	{
		if (ft_strncmp(var, "$", 2) == 0)
			env_val = ft_strdup(var);
		else if (ft_strncmp(var, "$?", 3) == 0)
			env_val = ft_itoa(info.exit_code);
		else
		{
			env_val = ft_getenv(info.my_envp, var);
			f = 0;
		}
		*s = append_env_value(*s, &env_val, f);
	}
}

char	*replace_env_vars(const char *txt, t_info info, int i, int start)
{
	char	*s;
	char	*var;

	s = NULL;
	var = NULL;
	while (txt[i])
	{
		if (txt[i] == '$')
		{
			if (i != start)
				s = append_substring(s, txt, start, i);
			i++;
			var = extract_variable(txt, &i);
			replace_env_norm(var, info, &s);
			free(var);
			start = i;
		}
		else
			i++;
	}
	if (i != start)
		s = append_substring(s, txt, start, i);
	return (s);
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
