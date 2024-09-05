#include "minishell.h"

static char	*get_cmd(char **paths, char *cmd)
{
	char	*try;
	
	while (*paths)
	{
		try = ft_strjoin(ft_strjoin(*paths, "/"), cmd);
		if (access(try, X_OK) == 0)
			return(try);
		paths++;
	}
	printf("cmd \"%s\" doesn\'t exist\n", cmd);
	return (NULL);
}

void cmd_to_path(t_cmd *cmd_lst, t_data data)
{
    while (cmd_lst)
    {
        cmd_lst->args[0] = get_cmd(data.paths,cmd_lst->args[0]);
        cmd_lst = cmd_lst->next;
    }
}