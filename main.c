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

void	substitute_vars(t_token *lst)
{
	int i;
	int start;
	char *s;
	char *v;
	
	s = NULL;
	i = 0;
	start = 0;
	while(lst)
	{
		if (lst->type == VAR)
		{printf("dkcvwjkws\n");
			while((lst->txt)[i])
			{
				if ((lst->txt)[i] == '$')
				{
					if (i != start)
						s = ft_strjoin(s, ft_strcpy(lst->txt, start, i - 1));
					start = ++i;
					while((lst->txt)[i] && !(ft_isalnum((lst->txt)[i]) || (lst->txt)[i] == '_'))
						i++;
					i--;
					v = ft_strcpy((lst->txt), start, i);
					s = ft_strjoin(s, getenv(v));
					start = i + 1;
				}
				i++;
			}
			lst->txt = ft_strdup(s);
			
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
		substitute_vars(token_lst);
		print_list(token_lst);
		free(input);
		free_lst(&token_lst);
	}
	return (0);
}