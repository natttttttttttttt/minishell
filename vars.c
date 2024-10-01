
#include "minishell.h"

// static void	save_part(int i, int start, char *str, char **s)
// {
// 	char	*tmp;

// 	if (i != start)
// 	{
// 		tmp = malloc(sizeof(char) * (i - start + 1));
// 		ft_strncpy(tmp, str, i - start);
// 		*s = ft_strjoin(*s, tmp);
// 		free(tmp);
// 	}
// }

// static void	replace_txt(t_token *lst, char **s, char *env_val)
// {
// 	if (!env_val)
// 		lst->txt = ft_strdup("");
// 	else
// 		lst->txt = ft_strdup(*s);
// 	lst->type = WORD;
// }

// static void	get_exit_code(t_token *lst, t_info info)
// {
// 	free(lst->txt);
// 	lst->txt = ft_itoa(info.exit_code);
// 	lst->type = WORD;
// 	lst = lst->next;
// }

void	vars_to_value(t_token *lst, int i, int start, t_info info)
{
	char	*s;
	char	*v;
	char	*tmp;
	char	*env_val;

	while (lst)
	{
		if (lst->type == VAR)
		{
			if (ft_strncmp(lst->txt, "$?", 3) == 0)
			{
				free(lst->txt);
				lst->txt = ft_itoa(info.exit_code);
				lst->type = WORD;
				lst = lst->next;
				continue ;
			}
			s = NULL;
			tmp = NULL;
			i = 0;
			start = 0;
			while ((lst->txt)[i])
			{
				if ((lst->txt)[i] == '$')
				{
					if (i != start)
					{
						tmp = malloc(sizeof(char) * (i - start + 1));
						ft_strncpy(tmp, lst->txt + start, i - start);
						s = ft_strjoin(s, tmp);
						free(tmp);
					}
					start = ++i;
					while ((lst->txt)[i] && (ft_isalnum((lst->txt)[i])
							|| (lst->txt)[i] == '_'))
						i++;
					v = malloc(sizeof(char) * (i - start + 1));
					ft_strncpy(v, lst->txt + start, i - start);
					env_val = ft_getenv(info.my_envp, v);
					free(v);
					if (s)
						tmp = ft_strdup(s);
					if (env_val && s)
					{
						free(s);
						s = ft_strjoin(tmp, env_val);
					}
					else if (env_val)
						s = ft_strdup(env_val);
					start = i;
					if (tmp)
						free(tmp);
				}
				else
					i++;
			}
			if (i != start)
			{
				tmp = malloc(sizeof(char) * (i - start + 1));
				ft_strncpy(tmp, lst->txt + start, i - start);
				
				s = ft_strjoin(s, tmp);
				free(tmp);
			}
			free(lst->txt);
			if (!s)
				lst->txt = ft_strdup("");
			else
				lst->txt = ft_strdup(s);
			if (s)
				free(s);
			lst->type = WORD;
		}
		lst = lst->next;
	}
}