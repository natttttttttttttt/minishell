#include "minishell.h"
//can norminette
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

static char	*deal_with_quotes(char *s, int q)
{
	char	*res;
	int		l;
	int		j;
	int		i;

	l = ft_strlen(s);
	if (q == 1 || (q == 2 && !(ft_strchr(s, '$'))))
		l = l - 2;
	else if (q == 2 && ft_strchr(s, '$'))
		l--;
	res = malloc(l + 1);
	i = 0;
	j = 0;
	while (s[i])
	{
		if ((q == 1 && s[i] == '\'')
			|| ((q == 2 && s[i] == '\"') && (ft_strchr(s, '$') > &s[i]))
			|| (q == 2 && (((ft_strchr(s, '$')) && (ft_strchr(s, '\"') == &s[i]))
					|| (!(ft_strchr(s, '$')) && s[i] == '\"'))))
			i++;
		else
			res[j++] = s[i++];
	}
	res[j] = '\0';
	return (res);
}

void	save_word(t_token **lst, char *word, int q)
{
	char	*tmp;

	tmp = deal_with_quotes(word, q);
	if (ft_strchr(word, '$') && q != 1)
		lst_add_back(lst, lst_create(tmp, VAR));
	else
		lst_add_back(lst, lst_create(tmp, WORD));
	free (word);
	free(tmp);
}

static void	quotes_err(int *quotes)
{
	printf("unexpected EOF while looking for matching \'\n");
	*quotes = -1;
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
			quotes_err(quotes);
	}
	else if (str[*i] == '\"')
	{
		(*i)++;
		while (str[*i] && str[*i] != '\"')
			(*i)++;
		if (str[*i] != '\0')
			*quotes = 2;
		else
			quotes_err(quotes);
	}
}

static void	save_tokens_norm(int i, int start, int *quotes, t_token **lst, char *str)
{
	if (i != start)
	{
		if (*quotes)
		{
			save_word(lst, copy_word(str, i, start), *quotes);
			*quotes = 0;
		}
		else
			save_word(lst, copy_word(str, i, start), *quotes);
	}
}
int	save_tokens(char *str, t_token **lst, t_info *info)
{
	int	i;
	int	start;
	int	sep;
	int	quotes;

	i = 0;
	start = 0;
	quotes = 0;
	while ((str[i] > 8 && str[i] < 14) || str[i] == 32)
	{
		i++;
		start++;
	}
	while (str[i])
	{
		find_quotes(str, &i, &quotes);
		if (quotes == -1)
		{
			info->exit_code = 2;
			free_token_lst(*lst);
			return (0);
		}
		sep = not_words(str, i);
		if (sep)
		{
			save_tokens_norm(i, start, &quotes, lst, str);
			if (sep != SPACES)
				lst_add_back(lst, lst_create(NULL, sep));
			if (sep == HEREDOC || sep == APPEND)
				i++;
			start = i + 1;
		}
		i++;
	}
	save_tokens_norm(i, start, &quotes, lst, str);
	lst_add_back(lst, lst_create(NULL, DONE));
	return (1);
}
