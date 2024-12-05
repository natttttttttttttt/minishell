/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pibouill <pibouill@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 13:00:57 by pibouill          #+#    #+#             */
/*   Updated: 2024/11/24 13:04:33 by pibouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include <stdio.h>
//can norminette
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

void	free_before_exit(t_info *info)
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

//int	unset_builtin(char **args, t_info *info, int i, int j)
//{
//    int		n;
//    int		k;
//    int		remove;
//    char	**new_env;

//    if (args[1] == NULL)
//        return (0);
//    while (args[i] && find_env_var(info->my_envp, args[i]) != -1)
//    {
//        j++;
//        i++;
//    }
//    n = 0;
//    while (info->my_envp[n] != NULL)
//        n++;
//    new_env = malloc(sizeof(char *) * (n + 1 - j));
//    if (!new_env)
//    {
//        perror("malloc");
//        return (errno);
//    }
//    i = 0;
//    j = 0;
//    while (i < n)
//    {
//        remove = 0;
//        k = 1;
//        while (args[k])
//        {
//            if (ft_strncmp(info->my_envp[i], args[k], ft_strlen(args[k])) == 0
//                && info->my_envp[i][ft_strlen(args[k])] == '=')
//            {
//                remove = 1;
//                break ;
//            }
//            k++;
//        }
//        if (!remove)
//            new_env[j++] = info->my_envp[i];
//        i++;
//    }
//    new_env[j] = NULL;
//    free(info->my_envp);
//    info->my_envp = new_env;
//    return (0);
//}

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
