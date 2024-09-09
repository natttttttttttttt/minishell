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

void cd_builtin(char **args, t_info info)
{
    char *dir;

    
    if (args[1] == NULL)
        dir = ft_getenv(info.my_envp, "HOME");
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

int valid_var_name(char *s)
{
    int i;
    i = 0;

    if (s == NULL)
        return (0);
    if (!((s[0] >= 'a' && s[0] <= 'z') || (s[0] >= 'A' && s[0] <= 'Z') || s[0] == '_'))
        return (0);
    while (s[i])
    {
        if (ft_isalnum(s[i]) || s[i] == '_')
            i++;
        else
            return (0);
    }
    return (1);
}
static char **split_for_export(char *s)
{
    int i;
    int j;
    int l;
    char **res;

    i = 0;
    j = 0;
    l = ft_strlen(s);
    res = malloc(sizeof(char *) * 3);
    res[2] = NULL;
    while (s[i] && s[i] != '=')
    {
        i++;
        j++;
    }
    if (j < l - 1)
    {
        i = 0;
        res[0] = malloc(sizeof(char) * j);
        res[0][j] = '\0';
        while (i < j)
        {
            res[0][i] = s[i];
            i++;
        }   
        res[1] = malloc(sizeof(char) * (l - j));
        res[1][l - j] = '\0';
        i = 0;
        j++;
        while (s[j])
        {
            res[1][i] = s[j];
            i++;
            j++;
        } 
    }
    else
    {
        res[0] = ft_strabcpy(s, 0, ft_strlen(s) - 2);;
        res[1] = NULL;
    }
    return (res);
}
void export_builtin(char **args, t_info info)
{
    char **split;
    char *var;
    char *value;
    int i;

    i = 0;
    while (args[i])
    {
        split = split_for_export(args[i]);
        if (split[0] && split[1])
        {
            var = split[0];
            value = split[1];
            if (valid_var_name(var))
                update_env(var, value, info.my_envp);
            else
                printf("export: %s: not a valid identifier\n", args[i]);
        }
        else
        {
            if (split[0] && valid_var_name(split[0]))
            {
                if (args[i][ft_strlen(args[i]) - 1] == '=')
                    update_env(var, "", info.my_envp);
            }
            else
                printf("export: %s: not a valid identifier\n", args[i]);
        }
        free(var);
        free(value);
        //free_arr(split);
    }
}