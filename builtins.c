#include "minishell.h"

int	is_builtin(t_cmd *cmd)
{
	if (ft_strncmp(cmd->args[0], "pwd", 4) == 0)
		return (BUILTIN_PWD);
	else if (ft_strncmp(cmd->args[0], "cd", 3) == 0)
		return (BUILTIN_CD);
	else if (ft_strncmp(cmd->args[0], "echo", 5) == 0)
		return (BUILTIN_ECHO);
	else if (ft_strncmp(cmd->args[0], "exit", 5) == 0)
		return (BUILTIN_EXIT);
	else if (ft_strncmp(cmd->args[0], "export", 7) == 0)
		return (BUILTIN_EXPORT);
	else if (ft_strncmp(cmd->args[0], "env", 4) == 0)
		return (BUILTIN_ENV);
	else if (ft_strncmp(cmd->args[0], "unset", 5) == 0)
		return (BUILTIN_UNSET);
	else
		return (0);
}

int	pwd_builtin(void)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (cwd)
	{
		printf("%s\n", cwd);
		free(cwd);
		return (0);
	}
	else
	{
		perror("pwd");
		return (errno);
	}
}

int	cd_builtin(char **args, t_info *info)
{
	char	*oldpwd;
	char	*newpwd;
	char	*dir;
//add -
	if (!args[1])
		dir = ft_getenv(info->my_envp, "HOME");
	else if (args[2])
	{
		printf("cd: too many arguments\n");
		return (1);
	}
	else
		dir = args[1];
	oldpwd = getcwd(NULL, 0);
	if (oldpwd == NULL)
	{
		perror("getcwd");
		return (errno);
	}
	if (chdir(dir) != 0)
	{
		perror("cd");
		free(oldpwd);
		return (1);
	}
	newpwd = getcwd(NULL, 0);
	if (newpwd == NULL)
	{
		perror("getcwd");
		free(oldpwd);
		return (errno);
	}
	update_env("OLDPWD", oldpwd, &info->my_envp);
	update_env("PWD", newpwd, &info->my_envp);
	free(oldpwd);
	free(newpwd);
	return (0);
}

static void	free_before_exit(t_info *info)
{
	free_command_list(info->cmds);
	free_token_lst(info->tokens);
	free(info->input);
	free_arr(info->paths);
	free_arr(info->my_envp);
}

void	exit_builtin(char **args, t_info *info)
{
	int	code;

	code = 0;
	if (args[1] != NULL)
	{
		if (args[2] != NULL)
		{
			printf("exit: too many arguments\n");
			free_before_exit(info);
			exit (1);
		}
		if (all_digits(args[1]))
			code = ft_atoi(args[1]);
		else
		{
			printf("exit\n");
			printf("exit: %s: numeric argument required\n", args[1]);
			free_before_exit(info);
			exit (2);
		}
	}
	printf("exit\n");
	free_before_exit(info);
	exit(code);
}

int	valid_var_name(char *s)
{
	int	i;

	i = 0;
	if (s == NULL)
		return (0);
	if (!((s[0] >= 'a' && s[0] <= 'z')
			|| (s[0] >= 'A' && s[0] <= 'Z') || s[0] == '_'))
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

static char	**split_for_export(char *s)
{
	int		i;
	int		l;
	char	**res;

	l = ft_strlen(s);
	res = malloc(sizeof(char *) * 3);
	if (!res)
	{
		perror("malloc");
		return (NULL);
	}
	res[2] = NULL;
	i = 0;
	while (s[i] && s[i] != '=')
		i++;
	if (s[i] == '=')
	{
		res[0] = malloc(sizeof(char) * (i + 1));
		if (!res[0])
		{
			perror("malloc");
			return (NULL);
		}
		ft_strncpy(res[0], s, i);
		if (s[i + 1])
		{
			res[1] = malloc(sizeof(char) * (l - i));
			if (!res[1])
			{
				perror("malloc");
				return (NULL);
			}
			ft_strncpy(res[1], s + i + 1, l - i - 1);
		}
	}
	else
	{
		res[0] = ft_strdup(s);
		res[1] = NULL;
	}
	return (res);
}

int	export_builtin(char **args, t_info *info, int i)
{
	char	**split;
	char	*var;
	char	*value;
	int		f;

	f = 0;
	while (args[i])
	{
		split = split_for_export(args[i]);
		if (!split)
			return (12);
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
		{
			printf("export: %s: not a valid identifier\n", var);
			f = 1;
		}
		free(split[0]);
		if (split[1])
			free(split[1]);
		free(split);
		i++;
	}
	return (f);
}

int	env_builtin(char **my_envp, int fd_out)
{
	int	i;

	i = 0;
	while (my_envp[i] != NULL)
	{
		write(fd_out, my_envp[i], ft_strlen(my_envp[i]));
		write(fd_out, "\n", 1);
		i++;
	}
	return (0);
}

int	unset_builtin(char **args, t_info *info, int i, int j)
{
	int		n;
	int		k;
	int		remove;
	char	**new_env;

	if (args[1] == NULL)
		return (0);
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
		return (errno);
	}
	i = 0;
	j = 0;
	while (i < n)
	{
		remove = 0;
		k = 1;
		while (args[k])
		{
			if (ft_strncmp(info->my_envp[i], args[k], ft_strlen(args[k])) == 0
				&& info->my_envp[i][ft_strlen(args[k])] == '=')
			{
				remove = 1;
				break ;
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
	return (0);
}

int	echo_builtin(char **args, int fd_out)
{
	int	i;
	int	n;

	i = 1;
	n = 1;
	if (args[i] && ft_strncmp(args[i], "-n", 3) == 0)
	{
		n = 0;
		i++;
	}
	while (args[i])
	{
		write(fd_out, args[i], ft_strlen(args[i]));
		if (args[i + 1])
			write(fd_out, " ", 1);
		i++;
	}
	if (n)
		write(fd_out, "\n", 1);
	return (0);
}
