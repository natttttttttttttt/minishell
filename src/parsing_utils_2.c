/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pibouill <pibouill@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 11:58:10 by pibouill          #+#    #+#             */
/*   Updated: 2025/01/28 12:11:01 by pibouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*
** Calculates adjusted string length after quote processing
** q: 1 for single quotes, 2 for double quotes
** orig_len: length of input string
** dollar_pos: position of $ in string, NULL if not present
** return: adjusted length after accounting for quotes to be removed 
*/
int	calculate_new_length(int q, int orig_len, char *dollar_pos)
{
	if (q == 1 || (q == 2 && !dollar_pos))
		return (orig_len - 2);
	else if (q == 2 && dollar_pos)
		return (orig_len - 1);
	return (orig_len);
}

/*
** Determines if current character should be skipped in quote processing
** q: 1 for single quotes, 2 for double quotes
** dollar_pos: position of $ in string, NULL if not present
** quote: position of current quote being processe
*/
bool	should_skip(char c, int q, char *dollar_pos, char *quote)
{
	if (q == 1 && c == '\'')
		return (true);
	if (q == 2 && c == '\"')
	{
		if (!dollar_pos || dollar_pos > quote || *quote == c)
			return (true);
	}
	return (false);
}
