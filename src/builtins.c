/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pibouill <pibouill@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 13:00:57 by pibouill          #+#    #+#             */
/*   Updated: 2024/12/06 13:37:55 by pibouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include <stdio.h>
#include <errno.h>

int	pwd_builtin(void)
{
	char	cwd[PATH_MAX];

	if (getcwd(cwd, sizeof(cwd)))
	{
		printf("%s\n", cwd);
		return (0);
	}
	else
	{
		perror("pwd");
		return (errno);
	}
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
			printf("exit\nexit: %s: numeric argument required\n", args[1]);
			free_before_exit(info);
			exit (2);
		}
	}
	printf("exit\n");
	free_before_exit(info);
	exit(code);
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

int	echo_builtin(char **args, int fd_out)
{
	int	i;
	int	nl_flag;

	i = 1;
	nl_flag = 1;
	if (args[i] && ft_strncmp(args[i], "-n", 3) == 0)
	{
		nl_flag = 0;
		i++;
	}
	while (args[i])
	{
		write(fd_out, args[i], ft_strlen(args[i]));
		if (args[i + 1])
			write(fd_out, " ", 1);
		i++;
	}
	if (nl_flag)
		write(fd_out, "\n", 1);
	return (0);
}
