#include "minishell.h"

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
		{
			while (1)
			{
				line = readline("> ");
				if (!line)
				{
					printf("warning: here-document delimited by end-of-file");
					printf(" (wanted '%s')\n", dlmtr[i]);
					break ;
				}
				if (ft_strncmp(line, dlmtr[i], ft_strlen(dlmtr[i]) + 1) == 0)
					break ;
				s = replace_env_vars(line, info, 0, 0);
				write(fd, s, ft_strlen(s));
				free(line);
				free(s);
				write(fd, "\n", 1);
			}
			close(fd);
		}
		i++;
	}
}
