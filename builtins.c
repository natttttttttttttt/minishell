#include "minishell.h"
void pwd_builtin(int fd)
{
    char *cwd;
    
    cwd= getcwd(NULL, 0);
    if (cwd)
    {
        write(fd, cwd, ft_strlen(cwd));
        free(cwd);
        return ;
    }
    else
        perror("pwd");
}