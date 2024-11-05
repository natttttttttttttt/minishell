/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vars_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pibouill <pibouill@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 16:36:07 by pibouill          #+#    #+#             */
/*   Updated: 2024/11/05 16:37:43 by pibouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	replace_env_norm(char *var, t_info info, char **s)
{
	char	*env_val;
	int		f;

	f = 1;
	if (var)
	{
		if (ft_strncmp(var, "$", 2) == 0)
			env_val = ft_strdup(var);
		else if (ft_strncmp(var, "$?", 3) == 0)
			env_val = ft_itoa(info.exit_code);
		else
		{
			env_val = ft_getenv(info.my_envp, var);
			f = 0;
		}
		*s = append_env_value(*s, &env_val, f);
	}
}

char	*replace_env_vars(const char *txt, t_info info, int i, int start)
{
	char	*s;
	char	*var;

	s = NULL;
	var = NULL;
	while (txt[i])
	{
		if (txt[i] == '$')
		{
			if (i != start)
				s = append_substring(s, txt, start, i);
			i++;
			var = extract_variable(txt, &i);
			replace_env_norm(var, info, &s);
			free(var);
			start = i;
		}
		else
			i++;
	}
	if (i != start)
		s = append_substring(s, txt, start, i);
	return (s);
}
