/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pibouill <pibouill@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 14:10:10 by pibouill          #+#    #+#             */
/*   Updated: 2024/12/06 14:10:10 by pibouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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
	char	*tmp;

	tmp = deal_with_quotes(word, q, 0);
	if (ft_strchr(word, '$') && q != 1)
		lst_add_back(lst, lst_create(tmp, VAR));
	else
		lst_add_back(lst, lst_create(tmp, WORD));
	free (word);
	free(tmp);
}

void	handle_separator(char *str, int *i, int *quotes, t_token **lst)
{
	int	sep;

	sep = not_words(str, i[0]);
	if (!sep)
		return ;
	if (i[0] != i[1])
	{
		save_word(lst, copy_word(str, i[0], i[1]), *quotes);
		*quotes = 0;
	}
	if (sep != SPACES)
		lst_add_back(lst, lst_create(NULL, sep));
	if (sep == HEREDOC || sep == APPEND)
		i[0]++;
	i[1] = i[0] + 1;
}

void	finalize_tokens(char *str, int *i, int quotes, t_token **lst)
{
	if (i[0] != i[1])
		save_word(lst, copy_word(str, i[0], i[1]), quotes);
	lst_add_back(lst, lst_create(NULL, DONE));
}
