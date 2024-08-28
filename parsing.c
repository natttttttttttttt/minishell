#include "minishell.h"

int	not_words(char *str, int i)
{
	if (((str[i] > 8 && str[i] < 14) || str[i] == 32))
		return (SPACES);
	else if (str[i] == '|')
		return (PIPE);
	else if (str[i] == '<' && str[i + 1] == '<')
		return (HEREDOC);
	else if (str[i] == '<' && str[i - 1] != '<')
		return (INPUT);
	else if (str[i] == '>' && str[i + 1] == '>')
		return (APPEND);
	else if (str[i] == '>' && str[i - 1] != '>')
		return (OUTPUT);
	else if (str[i] == '\0')
		return (DONE);
	else
		return (0);
}

void	save_word(t_token **lst, char *str, int i, int start)
{
	char	*word;
	int		j;

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

void	save_tokens(char *str, t_token **lst)
{
	int	i;
	int	start;
	int sep;
	int quotes;

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
		if (str[i] == '\'' && !quotes)
		{
			if (!quotes)
				quotes = 1;
			else
				quotes = 0;
		}
		if (str[i] == '\"')
		{
			if (!quotes)
				quotes = 2;
			else
				quotes = 0;
		}
		sep = not_words(str, i);
		if (sep)
		{
			if (i != start)
				save_word(lst, str, i, start);
			if (sep != SPACES)
				save_sep(lst, str, i, sep);
			if (sep == HEREDOC || sep == APPEND)
			{
				i++;
				start++;
			}
			start = i + 1;
		}
		i++;
	}
	if (i != start)
		save_word(lst, str, i, start);
	lst_add_back(lst, lst_create("\0", DONE));
}