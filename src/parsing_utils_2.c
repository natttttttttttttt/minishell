/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pibouill <pibouill@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 11:58:10 by pibouill          #+#    #+#             */
/*   Updated: 2025/01/28 12:11:01 by pibouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int q_mode(int q, char c)
{
    if (c == '\'')
    {
        if (q == 2)
            return (2);
        else if (q == 0)
                return (1);
        else if (q == 1)
                return (0);
    }
    else if (c == '\"')
    {
        if (q == 1)
            return (1);
        else if (q == 0)
                return (2);
        else if (q == 2)
                return (0);
    }
	return (q);
}

void    add_buf(char **buf, char c)
{
    char    *tmp;
    int     i;

    if (!buf)
        *buf = ft_strdup("\0");
    tmp = ft_strdup(*buf);
    i = 0;
    free(*buf);
    *buf = malloc(ft_strlen(tmp) + 2);
    while (i < ft_strlen(tmp))
    {
        (*buf)[i] = tmp[i];
        i++;
    }
    (*buf)[i] = c;
    (*buf)[i + 1] = '\0';
    free(tmp);
}

void add_var(int *i, char *s, t_info *info, char **buf, int j)
{
    char *var;
    char *env;

    var = NULL;
    env = NULL;
    if (s[*i] && s[*i] == '?')
    {
        env = ft_itoa(info->exit_code);
        (*i)++;
    }
    else if (s[*i] && !ft_isdigit(s[*i]))
    {
        while (ft_isalnum(s[*i]) || s[*i] == '_')
            add_buf(&var, s[(*i)++]);
        if (var)
        {
            env = ft_strdup(ft_getenv(info->my_envp, var));
            free(var);
        }
    }
    else 
        add_buf(buf, '$');
    while (env && env[j])
            add_buf(buf, env[j++]);
    if (env)
        free(env);
}

char    *deal_with_quotes(char *s, t_info *info)
{
    char *buf;
    int i;
    int q;

    buf = ft_strdup("");
    q = 0;
    i = 0;
    while (s[i])
    {
        while ((s[i] == '\'' && q != 2) || (s[i] == '\"' && q != 1))
        {
            q = q_mode(q, s[i]);
            i++;
        }
        if (s[i] && s[i] == '$' && q != 1)
        {
			i++;
			add_var(&i, s, info, &buf, 0);
		}
        else if (s[i])
        {    
			add_buf(&buf, s[i]);
        	i++;
		}
    }
	return (buf);
}