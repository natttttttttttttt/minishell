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

void cd_builtin(char **args, t_info *info)
{
    char *oldpwd;
    char *newpwd;

    oldpwd = getcwd(NULL, 0);
    if (oldpwd == NULL)
    {
        perror("getcwd");
        return;
    }
    if (chdir(args[1]) != 0)
    {
        perror("chdir");
        return;
    }
    newpwd = getcwd(NULL, 0);
    if (newpwd == NULL) {
        perror("getcwd");
        return;
    }
    update_env("OLDPWD", oldpwd, &info->my_envp);
    update_env("PWD", newpwd, &info->my_envp);
    free(oldpwd);
    free(newpwd);
}

void exit_builtin(char **args)
{
    int code = 0; 
    
    if (args[1] != NULL)
        if (all_digits(args[1]))
            code = ft_atoi(args[1]);  
    exit(code);
}

static int valid_var_name(char *s)
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
    int l;
    char **res;

    l = ft_strlen(s);
    res = malloc(sizeof(char *) * 3);
    res[2] = NULL;
    i = 0;
    while (s[i] && s[i] != '=')
        i++;
    if (s[i] == '=')
    {
        res[0] = malloc(sizeof(char) * (i + 1));
        strncpy(res[0], s, i);
        res[0][i] = '\0'; 
        res[1] = malloc(sizeof(char) * (l - i + 1));
        ft_strncpy(res[1], s + i + 1, l - i);
        res[1][l - i] = '\0'; 
    }
    else
    {
        res[0] = ft_strdup(s);
        res[1] = NULL;
    }
    return res;
}

void export_builtin(char **args, t_info *info)
{
    char **split;
    char *var;
    char *value;
    int i;

    i = 1;
    while (args[i])
    {
        split = split_for_export(args[i]);
        var = split[0];
        if (split[1] != NULL)
            value = split[1];
        else
            value = "";
        if (valid_var_name(var))
        {
            if (value || args[i][ft_strlen(args[i]) - 1] == '=')
                update_env(var, value, &(info->my_envp));
        }
        else
            printf("export: %s: not a valid identifier\n", var);
        free(split[0]);
        if (split[1])
            free(split[1]);
        free(split);
        i++;
    }
}

void builtin_env(char **my_envp)
{
    int i ;

    i = 0;
    while (my_envp[i] != NULL) 
    { 
        printf("%s\n", my_envp[i]);
        i++;
    }
}

void unset_builtin(char **args, t_info *info)
{
    int i;
    int j;
    int n;
    int k;
    int remove;
    char **new_env;
    
    if (args[1] == NULL)
        return;
    i = 1;
    j = 0;
    while (args[i] && find_env_var(info->my_envp, args[i]) != -1)
    {
        j++;
        i++;
    }
    n = 0;
    while (info->my_envp[n] != NULL)
        n++;
    new_env = malloc(sizeof(char *) * (n + 1 - j));
    if (!new_env)
    {
        perror("malloc");
        return;
    }
    i = 0;
    j = 0;
    while (i < n)
    {
        remove = 0;
        k = 1;
        while (args[k])
        {
            if (ft_strncmp(info->my_envp[i], args[k], ft_strlen(args[k])) == 0 &&
                info->my_envp[i][ft_strlen(args[k])] == '=')
            {
                remove = 1;
                break;
            }
            k++;
        }
        if (!remove)
            new_env[j++] = info->my_envp[i];
        i++;
    }
    new_env[j] = NULL;
    free(info->my_envp);
    info->my_envp = new_env;
}