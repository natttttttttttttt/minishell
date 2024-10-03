
#include "minishell.h"

// static void	save_part(int i, int start, char *str, char **s)
// {
// 	char	*tmp;

// 	if (i != start)
// 	{
// 		tmp = malloc(sizeof(char) * (i - start + 1));
// 		ft_strncpy(tmp, str, i - start);
// 		*s = ft_strjoin(*s, tmp);
// 		free(tmp);
// 	}
// }

// static void	replace_txt(t_token *lst, char **s, char *env_val)
// {
// 	if (!env_val)
// 		lst->txt = ft_strdup("");
// 	else
// 		lst->txt = ft_strdup(*s);
// 	lst->type = WORD;
// }

// static void	get_exit_code(t_token *lst, t_info info)
// {
// 	free(lst->txt);
// 	lst->txt = ft_itoa(info.exit_code);
// 	lst->type = WORD;
// 	lst = lst->next;
// }

void vars_to_value(t_token *lst, int i, int start, t_info info)
{
    char *s;
    char *v;
    char *tmp;
    char *env_val;

    while (lst)
    {
        if (lst->type == VAR)
        {
            if (ft_strncmp(lst->txt, "$?", 3) == 0)
            {
                free(lst->txt);
                lst->txt = ft_itoa(info.exit_code);
                lst->type = WORD;
                lst = lst->next;
                continue;
            }

            s = NULL;  // Initialize `s` to NULL
            tmp = NULL;
            env_val = NULL;
            i = 0;
            start = 0;
            while ((lst->txt)[i])
            {
                if ((lst->txt)[i] == '$')
                {
                    if (i != start)
                    {
                        tmp = malloc(sizeof(char) * (i - start + 1));  // Allocate memory for tmp
                        ft_strncpy(tmp, lst->txt + start, i - start);  // Copy substring
                        tmp[i - start] = '\0';  // Null-terminate the string

                        // If `s` is NULL, just duplicate `tmp`, no need to join
                        if (!s)
                        {
                            s = ft_strdup(tmp);  // Copy `tmp` to `s` since `s` is empty
                        }
                        else
                        {
                            // If `s` is not NULL, join `s` and `tmp`
                            char *joined = ft_strjoin(s, tmp);  // Join s and tmp
                            free(s);  // Free old s to avoid leak
                            s = joined;  // Assign new value to s
                        }
                        free(tmp);  // Free tmp after use
                    }
                    start = ++i;
                    while ((lst->txt)[i] && (ft_isalnum((lst->txt)[i]) || (lst->txt)[i] == '_'))
                        i++;

                    v = malloc(sizeof(char) * (i - start + 1));  // Allocate memory for variable
                    ft_strncpy(v, lst->txt + start, i - start);  // Copy variable name
                    v[i - start] = '\0';  // Null-terminate the variable name

                    env_val = ft_getenv(info.my_envp, v);  // Get environment variable
                    free(v);  // Free variable name after use

                    char *tmp_s = s ? ft_strdup(s) : NULL;  // Backup current `s`
                    if (env_val)
                    {
                        if (s)
                        {
                            free(s);  // Free old `s`
                            s = ft_strjoin(tmp_s, env_val);  // Join old string with env_val
                        }
                        else
                        {
                            s = ft_strdup(env_val);  // No `s` yet, so just duplicate env_val
                        }
                    }
                    if (tmp_s)
                        free(tmp_s);  // Free backup string

                    start = i;
                }
                else
                {
                    i++;
                }
            }

            // Handle remaining part of the string after the last '$'
            if (i != start)
            {
                tmp = malloc(sizeof(char) * (i - start + 1));  // Allocate memory for the remaining part
                ft_strncpy(tmp, lst->txt + start, i - start);  // Copy remaining part of the string
                tmp[i - start] = '\0';  // Null-terminate the string

                if (!s)
                {
                    s = ft_strdup(tmp);  // If `s` is empty, just copy `tmp`
                }
                else
                {
                    char *joined = ft_strjoin(s, tmp);  // Join s and tmp
                    free(s);  // Free old s
                    s = joined;  // Assign the new value to s
                }
                free(tmp);  // Free tmp after use
            }

            free(lst->txt);  // Free original text
            lst->txt = s ? ft_strdup(s) : ft_strdup("");  // Assign new value to token
            free(s);  // Free the concatenated result

            lst->type = WORD;
        }
        lst = lst->next;  // Move to the next token
    }
}

