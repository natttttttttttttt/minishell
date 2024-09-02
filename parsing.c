#include "minishell.h"

int	not_words(char *str, int i)
{
	if (((str[i] > 8 && str[i] < 14) || str[i] == 32))
		return (SPACES);
	else if (str[i] == '|')
		return (PIPE);
	else if (str[i] == '<' && str[i + 1] == '<')
		return (HEREDOC);
	else if (str[i] == '<')
		return (INPUT);
	else if (str[i] == '>' && str[i + 1] == '>')
		return (APPEND);
	else if (str[i] == '>')
		return (OUTPUT);
	else if (str[i] == '\0')
		return (DONE);
	else
		return (0);
}

char	*copy_word(char *str, int i, int start)
{
	char	*word;
	int		j;

	word = malloc(sizeof(char) * (i - start + 1));
	j = 0;
	while (start < i)
		word[j++] = str[start++];
	word[j] = '\0';
	return (word);
}

void	save_word(t_token **lst, char *word, int q)
{
	if (ft_strchr(word, '$') && q != 1)
		lst_add_back(lst, lst_create(word, VAR));
	else
		lst_add_back(lst, lst_create(word, WORD));
	free (word);
}

void	save_sep(t_token **lst, char *str, int i, int type)
{
	char	*separator;

	if (type == APPEND || type == HEREDOC)
	{
		separator = malloc(sizeof(char) * 3);
		separator[0] = str[i];
		separator[1] = str[i + 1];
		separator[2] = '\0';
	}
	else
	{
		separator = malloc(sizeof(char) * 2);
		separator[0] = str[i];
		separator[1] = '\0';
	}
	lst_add_back(lst, lst_create(separator, type));
	free(separator);
}

void	find_quotes(char *str, int *i, int *quotes)
{
	if (str[*i] == '\'')
	{
		(*i)++;
		while (str[*i] && str[*i] != '\'')
			(*i)++;
		if (str[*i] != '\0')
			*quotes = 1;
		else
			printf("one quote\n");
	}
	if (str[*i] == '\"')
	{
		(*i)++;
		while (str[*i] && str[*i] != '\"')
			(*i)++;
		if (str[*i] != '\0')
			*quotes = 2;
		else
			printf("one quote\n");
	}
}

void	save_tokens(char *str, t_token **lst)
{
	int	i;
	int	start;
	int	sep;
	int	quotes;

	i = 0;
	start = 0;
	quotes = 0;

	while (str[i] > 8 && str[i] < 14 || str[i] == 32)
	{
		i++;
		start++;
	}
	while (str[i])
	{
		find_quotes(str, &i, &quotes);
		sep = not_words(str, i);
		if (sep)
		{
			if (i != start)
			{
				if (quotes)
				{
					save_word(lst, copy_word(str, i - 1, ++start), quotes);
					quotes = 0;
				}
				else
					save_word(lst, copy_word(str, i, start), quotes);
			}
			if (sep != SPACES)
				save_sep(lst, str, i, sep);
			if (sep == HEREDOC || sep == APPEND)
				i++;
			start = i + 1;
		}
		i++;
	}
	if (i != start)
	{
		if (quotes)
		{
			save_word(lst, copy_word(str, i - 1, ++start), quotes);
			quotes = 0;
		}
		else
			save_word(lst, copy_word(str, i, start), quotes);
	}
	lst_add_back(lst, lst_create("\0", DONE));
}
