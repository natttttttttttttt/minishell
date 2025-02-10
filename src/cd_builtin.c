/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pibouill <pibouill@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 13:22:45 by pibouill          #+#    #+#             */
/*   Updated: 2024/12/05 13:22:47 by pibouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include <linux/limits.h>

char	*change_dir(char **args, t_info *info)
{
	char	*dir;

	if (!args[1])
		dir = ft_getenv(info->my_envp, "HOME");
	else if (args[2])
	{
		printf("cd: too many arguments\n");
		return (NULL);
	}
	else
		dir = args[1];
	return (dir);
}

int	cd_to_oldpwd(t_info *info)
{
	char	*oldpwd;

	oldpwd = ft_getenv(info->my_envp, "OLDPWD");
	if (!oldpwd)
	{
		perror("cd: OLDPWD not set.");
		return (1);
	}
	printf("%s\n", oldpwd);
	if (chdir(oldpwd) != 0)
	{
		perror("cd -");
		return (1);
	}
	return (0);
}

// https://shorturl.at/zINwb
void	update_pwd_env(char *oldpwd, char *newpwd, char ***envp)
{
	if (!ft_getenv(*envp, "OLDPWD"))
		update_env("OLDPWD", oldpwd, envp);
	else
		update_env("OLDPWD", oldpwd, envp);
	update_env("PWD", newpwd, envp);
}

int	cd_builtin(char **args, t_info *info)
{
	char	oldpwd[PATH_MAX];
	char	newpwd[PATH_MAX];
	char	*dir;

	dir = change_dir(args, info);
	if (!dir)
		return (1);
	if (*dir == '-')
		return (cd_to_oldpwd(info));
	if (getcwd(oldpwd, PATH_MAX) == NULL)
		return (perror("getcwd"), 1);
	if (chdir(dir) != 0)
		return (perror("cd"), 1);
	if (getcwd(newpwd, PATH_MAX) == NULL)
		return (perror("getcwd"), 1);
	update_pwd_env(oldpwd, newpwd, &info->my_envp);
	return (0);
}
