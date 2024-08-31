#include "minishell.h"

int	all_spaces(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if ((str[i] > 8 && str[i] < 14) || str[i] == 32)
			i++;
		else
			return (0);
	}
	return (1);
}

int	parsing(char *str)
{
	if (!str)
		return (0);
	if (str[0] == '\0' || str[0] == '\n')
		return (0);
	if (all_spaces(str))
		return (0);
	return (1);
}

void	substitute_vars(t_token *lst, int i, int start)
{
	char	*s;
	char	*v;
	char	*tmp;
	char 	*env_val;
	
	while (lst)
	{
		if (lst->type == VAR)
		{
			s = ft_strdup("");
			i = 0;
			start = 0;
			while ((lst->txt)[i])
			{
				if ((lst->txt)[i] == '$')
				{
					if (i != start)
					{
						tmp = s;
						s = ft_strjoin(s, ft_strcpy(lst->txt, start, i - 1));
						free(tmp);
					}
					start = i + 1;
					i++;
					while ((lst->txt)[i] && (ft_isalnum((lst->txt)[i]) || (lst->txt)[i] == '_'))
						i++;
					v = ft_strcpy((lst->txt), start, i - 1);
					env_val = getenv(v);
					free(v);
					if (env_val)
					{
						tmp = s;
						s = ft_strjoin(s, env_val);
						free(tmp);
					}
					else 
						printf("var not found\n");
					start = i;
				}
				i++;
			}
			tmp = s;
			s = ft_strjoin(s, ft_strcpy(lst->txt, start, i - 1));
			free(tmp);
			free(lst->txt);
			lst->txt = ft_strdup(s);
			free(s);
		}
		lst = lst->next;
	}
}


int	main()
{
	char	*input;
	t_token	*token_lst;

	while (1)
	{
		token_lst = NULL;
		input = readline("minishell> ");
		if (parsing(input))
			save_tokens(input, &token_lst);
		substitute_vars(token_lst, 0, 0);
		print_list(token_lst);
		free(input);
		free_lst(&token_lst);
	}
	return (0);
}