/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pibouill <pibouill@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 11:04:54 by pibouill          #+#    #+#             */
/*   Updated: 2024/12/07 11:07:22 by pibouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	write_heredoc_line(int fd, char *line, t_info info)
{
	char	*s;

	s = replace_env_vars(line, info, 0, 0);
	write(fd, s, ft_strlen(s));
	write(fd, "\n", 1);
	free(line);
	free(s);
}

void	handle_single_heredoc(char *delimiter, t_info info)
{
	char	*line;
	int		fd;

	fd = open("heredoc.tmp", O_RDWR | O_CREAT | O_TRUNC, 0600);
	if (fd == -1)
	{
		perror("open");
		return ;
	}
	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			printf("warning: here-document delimited by end-of-file");
			printf(" (wanted '%s')\n", delimiter);
			break ;
		}
		if (ft_strncmp(line, delimiter, ft_strlen(delimiter) + 1) == 0)
			break ;
		write_heredoc_line(fd, line, info);
	}
	close(fd);
}

void	heredoc(char **dlmtr, t_info info)
{
	int	i;

	i = 0;
	while (dlmtr[i])
	{
		handle_single_heredoc(dlmtr[i], info);
		i++;
	}
}
