#include "minishell.h"

static char	*extract_variable(const char *txt, int *i)
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

static char	*append_substring(char *s, const char *txt, int start, int end)
{
	char	*tmp;
	char	*res;
	char	*copy;
	int		i;

	i = 0;
	copy = ft_strdup(&txt[start]);
	tmp = append_substr_norm(copy, txt, start, end);
	res = ft_strjoin(s, tmp);
	free(s);
	free(tmp);
	free(copy);
	return (res);
}

static char	*append_env_value(char *s, const char *env_val)
{
	char	*res;

	if (!env_val)
		env_val = "";
	if (s)
	{
		res = ft_strjoin(s, env_val);
		free(s);
	}
	else
		res = ft_strdup(env_val);
	return (res);
}

static void	replace_env_norm(char *var, t_info info, char **s)
{
	char	*env_val;

	if (var)
	{
		if (ft_strncmp(var, "$", 2) == 0)
			env_val = ft_strdup(var);
		else if (ft_strncmp(var, "$?", 3) == 0)
			env_val = ft_itoa(info.exit_code);
		else
			env_val = ft_getenv(info.my_envp, var);
		*s = append_env_value(*s, env_val);
	}
}

static char	*replace_env_vars(const char *txt, t_info info, int i, int start)
{
	char	*s;
	char	*var;

	s = NULL;
	while (txt[i])
	{
		if (txt[i] == '$')
		{
			if (i != start)
				s = append_substring(s, txt, start, i);
			i++;
			var = extract_variable(txt, &i);
			replace_env_norm(&var, info, &s);
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


void vars_to_value(t_token *lst, t_info info)
{
	char	*s;

	while (lst)
	{
		if (lst->type == VAR)
		{
			//handle_special_var(lst, info);
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
