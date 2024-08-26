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

int	not_words(char *str, int i)
{
	if (((str[i] > 8 && str[i] < 14) || str[i] == 32))
		return (SPACES);
	else if (str[i] == '|')
		return (PIPE);
	else if (str[i] == '\0')
		return (DONE);
	else
		return (0);
}

void save_tokens(char *str, t_token **lst)
{
	int	i;
	int	start;
	int j;
	char	*word;
    char *separator;

	i = 0;
	start = 0;
	while (str[i] > 8 && str[i] < 14 || str[i] == 32)
	{
		i++;
		start++;
	}
	while (str[i])
	{
		if (not_words(str, i))
		{
            if (i != start)
			{
				word = malloc(sizeof(char) * (i - start + 1));
				j = 0;
				while (start < i)
				{
					word[j] = str[start];
					start++;
					j++;
				}
				word[j] = '\0';
                if (word[0] == '$')
                    lst_add_back(lst, lst_create(word, VAR));
                else
				    lst_add_back(lst, lst_create(word, WORD));
                free(word);
			}
            separator = malloc(sizeof(char) * 2);
            separator[0] = str[i];
            separator[1] = '\0';
			lst_add_back(lst, lst_create(separator, not_words(str, i)));
            free(separator);
			start = i + 1;
		}
		i++;
	}
    if (i != start)
    {
        word = malloc(sizeof(char) * (i - start + 1)); 
        j = 0;
        while (start < i)
        {
            word[j++] = str[start++];
        }
        word[j] = '\0';
        if (word[0] == '$')
            lst_add_back(lst, lst_create(word, VAR));
        else
		   lst_add_back(lst, lst_create(word, WORD));
    }
    lst_add_back(lst, lst_create("\0", DONE));
    free(word);
}

void	free_lst(t_token **lst)
{
	t_token	*head;

	if (!lst || !(*lst))
		return ;
	while ((*lst)->next != NULL)
	{
		head = (*lst)->next;
		free(*lst);
		*lst = head;
	}
	free(*lst);
}

int	main()
{
	char	*input;
	t_token	*token_lst;

	
	while (1)
	{token_lst = NULL;
		input = readline("minishell> ");
		if (parsing(input))
            save_tokens(input, &token_lst);
        print_list(token_lst);
		free(input);
        free_lst(&token_lst);
	}
	
	return (0);
}