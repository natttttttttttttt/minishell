#include "minishell.h"

char **copy_envp(char **envp)
{
    int i;
    int n;
    int j;
    char **my_envp;

    i = 0;
    n = 0;
    while (envp[n] != NULL)
        n++;
    my_envp = malloc((n + 1) * sizeof(char *));
    if (!my_envp)
        return (NULL);
    while (i < n)
    {
        my_envp[i] = ft_strdup(envp[i]);
        if (!my_envp[i])
        {
            j = 0;
            while (j < i)
            {
                free(my_envp[j]);
                j++;
            }    
            free(my_envp);
            return (NULL);
        }
        i++;
    }
    my_envp[n] = NULL;
    return (my_envp);
}

char *ft_getenv(char **my_envp, char *var)
{
    int i;
    int len;
   
    i = 0;
    len = ft_strlen(var);
    while (my_envp[i] != NULL)
    {
        if (ft_strncmp(my_envp[i], var, len) == 0 && my_envp[i][len] == '=')
           return (my_envp[i] + len + 1);
        i++;
    } 
    return (NULL);
}

void update_env(const char *name, const char *value, char ***envp)
{
    int i = 0;
    size_t name_len = strlen(name);
    size_t value_len = strlen(value);
    size_t new_entry_len = name_len + value_len + 2; // +2 for '=' and '\0'

    // Create the new entry in the form of "NAME=value"
    char *new_entry = malloc(new_entry_len);
    if (!new_entry)
    {
        perror("malloc");
        return;
    }
    snprintf(new_entry, new_entry_len, "%s=%s", name, value);

    // Search for the environment variable
    while ((*envp)[i] != NULL)
    {
        if (strncmp((*envp)[i], name, name_len) == 0 && (*envp)[i][name_len] == '=')
        {
            // Variable found, update its value
            free((*envp)[i]);
            (*envp)[i] = new_entry;
            return;
        }
        i++;
    }

    // Variable not found, add it to the end of the array
    char **new_envp = realloc(*envp, (i + 2) * sizeof(char *));
    if (!new_envp)
    {
        perror("realloc");
        free(new_entry);
        return;
    }
    new_envp[i] = new_entry;
    new_envp[i + 1] = NULL;
    *envp = new_envp;
}

