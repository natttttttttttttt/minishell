#include "minishell.h"

int is_builtin(t_cmd *cmd)
{
    cmd->builtin = 1;
    if (strcmp(cmd->args[0], "pwd") == 0)
        return (BUILTIN_PWD);
    else if (strcmp(cmd->args[0], "cd") == 0)
        return (BUILTIN_CD);
    else if (strcmp(cmd->args[0], "echo") == 0)
        return (BUILTIN_ECHO);
    else if (strcmp(cmd->args[0], "exit") == 0)
        return (BUILTIN_EXIT);
    else if (strcmp(cmd->args[0], "export") == 0)
        return (BUILTIN_EXPORT);
    else if (strcmp(cmd->args[0], "env") == 0)
        return (BUILTIN_ENV);
    else if (strcmp(cmd->args[0], "unset") == 0)
        return (BUILTIN_UNSET);
    else
    {
        cmd->builtin = 0;
        return (0);
    }
}

void pwd_builtin()
{
    char *cwd;
    
    cwd = getcwd(NULL, 0);
    if (cwd)
    {

       write(1, cwd, ft_strlen(cwd));
        write(1, "\n", 1);
        free(cwd);
        return ;
    }
    else
        perror("pwd");
}

void cd_builtin(char **args)
{
    char *dir;

    
    if (args[1] == NULL)
        dir = getenv("HOME");
    else 
        dir = args[1];
    if (chdir(dir) != 0)
        perror("cd");
}

void exit_builtin(char **args)
{
    int code = 0; 
    
    if (args[1] != NULL)
        if (all_digits(args[1]))
            code = ft_atoi(args[1]);  
    exit(code);
}