#include "minishell.h"

void heredoc(char *delimiter)
{
	char    *line;
	int 	fd;

	line = NULL;

	fd = open("heredoc.tmp", O_RDWR | O_CREAT | O_TRUNC, 0600);
	if (fd == -1)
	{
		perror("open");
	}
	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			printf("warning: here-document delimited by end-of-file");
			printf("wanted '%s')\n", delimiter);
			break ;
		}
		if (ft_strncmp(line, delimiter, ft_strlen(delimiter) + 1) == 0)
			break ;
		write(fd, line, ft_strlen(line));
		free(line);
		write(fd, "\n", 1);
	}
	close(fd);
}
