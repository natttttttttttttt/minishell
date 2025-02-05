/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pibouill <pibouill@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 15:33:43 by pibouill          #+#    #+#             */
/*   Updated: 2025/02/05 15:34:08 by pibouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	q_mode(int q, char c)
{
	if (c == '\'')
	{
		if (q == 2)
			return (2);
		else if (q == 0)
			return (1);
		else if (q == 1)
			return (0);
	}
	else if (c == '\"')
	{
		if (q == 1)
			return (1);
		else if (q == 0)
			return (2);
		else if (q == 2)
			return (0);
	}
	return (q);
}

void	add_buf(char **buf, char c)
{
	char	*tmp;
	int		i;

	if (!buf)
		*buf = ft_strdup("\0");
	tmp = ft_strdup(*buf);
	i = 0;
	free(*buf);
	*buf = malloc(ft_strlen(tmp) + 2);
	while (i < ft_strlen(tmp))
	{
		(*buf)[i] = tmp[i];
		i++;
	}
	(*buf)[i] = c;
	(*buf)[i + 1] = '\0';
	free(tmp);
}
