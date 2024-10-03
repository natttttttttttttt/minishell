#include "minishell.h"

static char	*extract_variable(const char *txt, int *i)
{
	int		start;
	char	*var;

	start = *i;
	if (!(txt[*i] >= '0' && txt[*i] <='9'))
		while (txt[*i] && (ft_isalnum(txt[*i]) || txt[*i] == '_'))
			(*i)++;
	if (*i == start)
		return (NULL);
	var = malloc(sizeof(char) * (*i - start + 1));
	ft_strncpy(var, txt + start, *i - start);
	return (var);
}

static void	handle_special_var(t_token *lst, t_info info)
{
	if (ft_strncmp(lst->txt, "$", 2) == 0)
		lst->type = WORD;
	if (ft_strncmp(lst->txt, "$?", 3) == 0)
	{
		free(lst->txt);
		lst->txt = ft_itoa(info.exit_code);
		lst->type = WORD;
	}
}

static char	*append_substring(char *s, const char *txt, int start, int end)
{
	char	*tmp;
	char	*res;

	tmp = malloc(sizeof(char) * (end - start + 1));
	ft_strncpy(tmp, txt + start, end - start);
	res = ft_strjoin(s, tmp);
	free(s);
	free(tmp);
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

static char	*replace_env_vars(const char *txt, t_info info, int i, int start)
{
	char	*s;
	char	*var;
	char	*env_val;

	s = NULL;
	while (txt[i])
	{
		if (txt[i] == '$')
		{
			if (i != start)
				s = append_substring(s, txt, start, i);
			i++;
			var = extract_variable(txt, &i);
			if (var)
			{
				env_val = ft_getenv(info.my_envp, var);
				s = append_env_value(s, env_val);
				free(var);
			}
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
			handle_special_var(lst, info);
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
