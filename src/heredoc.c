/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pibouill <pibouill@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 16:10:48 by pibouill          #+#    #+#             */
/*   Updated: 2024/11/06 10:12:16 by pibouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	do_heredoc(char **dlmtr, t_info info, int *fd, int *i)
{
	char	*line;
	char	*s;

	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			printf("warning: here-document delimited by end-of-file");
			printf(" (wanted '%s')\n", dlmtr[*i]);
			break ;
		}
		if (ft_strncmp(line, dlmtr[*i], ft_strlen(dlmtr[*i]) + 1) == 0)
			break ;
		s = replace_env_vars(line, info, 0, 0);
		write(*fd, s, ft_strlen(s));
		free(line);
		free(s);
		write(*fd, "\n", 1);
	}
	close(*fd);
}

void	heredoc(char **dlmtr, t_info info)
{
	char	*line;
	char	*s;
	int		fd;
	int		i;

	i = 0;
	while (dlmtr[i])
	{
		fd = open("heredoc.tmp", O_RDWR | O_CREAT | O_TRUNC, 0600);
		if (fd == -1)
			perror("open");
		else
			do_heredoc(dlmtr, info, &fd, &i);
		i++;
	}
}
