/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pibouill <pibouill@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 18:27:12 by pibouill          #+#    #+#             */
/*   Updated: 2024/05/24 12:09:30 by pibouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

/*
** Returns an array of strings
** from the split of a string by char c
*/

static int	count(const char *str, char c)
{
	int	i;
	int	k;

	i = 0;
	k = 0;
	while (str[i])
	{
		if (str[i] != c)
		{
			k++;
			while (str[i] && str[i] != c)
				i++;
		}
		else
			i++;
	}
	return (k);
}

static void	ft_skip(const char *str, char c, int *i, int *from)
{
	while (str[*i] == c)
		(*i)++;
	*from = *i;
	while (str[*i] != c && str[*i])
		(*i)++;
}

char	**ft_split(const char *s, char c)
{
	int		i;
	int		k;
	int		j;
	int		from;
	char	**res;

	i = 0;
	k = 0;
	res = (char **)malloc((count(s, c) + 1) * sizeof(char *));
	if (!res)
		return (NULL);
	while (s[i])
	{
		ft_skip(s, c, &i, &from);
		if (from == i)
			break ;
		res[k] = (char *)malloc((i - from + 1) * sizeof(char));
		j = 0;
		while (from < i)
			res[k][j++] = s[from++];
		res[k][j] = '\0';
		k++;
	}
	res[k] = NULL;
	return (res);
}

void	*free_array(char **arr)
{
	size_t	i;

	i = 0;
	while (arr[i] != NULL)
		free(arr[i++]);
	free(arr);
	return (NULL);
}

// int main()
// {
//     const char *s = "fs nfid isdn i sdoif nsifnd ios ni i odfis";
//     char c = ' ';
// 	int	i = 0;
//     char **words = ft_split(s, c);

//     if (words)
// 	{
// 		while (words[i])
// 		{
// 			printf("Word at index %d: %s\n", i, words[i]);
// 			free(words[i]);
// 			i++;
// 		}
// 		free(words);
//     }
//     return (0);
// }
