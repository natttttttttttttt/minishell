/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pibouill <pibouill@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 11:58:10 by pibouill          #+#    #+#             */
/*   Updated: 2025/01/28 11:59:16 by pibouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	calculate_new_length(int q, int orig_len, char *dollar_pos)
{
	if (q == 1 || (q == 2 && !dollar_pos))
		return (orig_len - 2);
	else if (q == 2 && dollar_pos)
		return (orig_len - 1);
	return (orig_len);
}

bool	should_skip(char c, int q, char *dollar, char *quote)
{
	if (q == 1 && c == '\'')
		return (true);
	if (q == 2 && c == '\"')
	{
		if (!dollar || dollar > quote || *quote == c)
			return (true);
	}
	return (false);
}
