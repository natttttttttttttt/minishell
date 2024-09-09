#include "minishell.h"

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
        res[0] = ft_strabcpy(s, 0, ft_strlen(s) - 2);
        res[1] = NULL;
    }
    return (res);
}
int main()
{
    char *s = "aaaaa";
    char **ar = split_for_export(s);
    int i = 0;
    while(ar[i])
    {
        printf("%s\n", ar[i]);
        i++;
    }
}