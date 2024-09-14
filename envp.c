#include "minishell.h"

char	**copy_envp(char **envp)
{
	int		i;
	int		n;
	int		j;
	char	**my_envp;

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

char	*ft_getenv(char **my_envp, char *var)
{
	int	i;
	int	len;

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

int 	find_env_var(char **my_envp, char *var)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(var);
	while (my_envp[i])
	{
		if (ft_strncmp(my_envp[i], var, len) == 0 && my_envp[i][len] == '=')
			return (i);
		i++;
	}
	return (-1);
}

void	update_env(char *var, char *value, char ***my_envp)
{
	int		i;
	int		var_i;
	char	*s;
	char	**new_envp;

	s = malloc(sizeof(char) * (ft_strlen(var) + ft_strlen(value) + 2));
	if (!s)
	{
		perror("malloc");
		return ;
	}
	i = 0;
	while (i < ft_strlen(var))
	{
		s[i] = var[i];
		i++;
	}
	s[i++] = '=';
	while (i < ft_strlen(var) + ft_strlen(value) + 1)
	{
		s[i] = value[i - ft_strlen(var) - 1];
		i++;
	}
	s[i] = '\0';
	var_i = find_env_var(*my_envp, var);
	if (var_i != -1)
	{
		free((*my_envp)[var_i]);
		(*my_envp)[var_i] = s;
	}
	else
	{
		i = 0;
		while ((*my_envp)[i])
			i++;
		new_envp = malloc((i + 2) * sizeof(char *));
		if (!new_envp)
		{
			perror("malloc"); 
			return ;
		}
		var_i = 0;
		while (var_i < i)
		{
			new_envp[var_i] = (*my_envp)[var_i];
			var_i++;
		}
		new_envp[i] = ft_strdup(s);
		new_envp[i + 1] = NULL;
		free(*my_envp);
		*my_envp = new_envp;
		free(s);
	}
}
