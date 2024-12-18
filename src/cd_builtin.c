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
	char	*oldpwd;
	char	*newpwd;
	char	*dir;

	dir = change_dir(args, info);
	if (!dir)
		return (1);
	if (*dir == '-')
		return (cd_to_oldpwd(info));
	oldpwd = getcwd(NULL, 0);
	if (chdir(dir) != 0)
		return (free(oldpwd), perror("cd"), 1);
	newpwd = getcwd(NULL, 0);
	if (!newpwd)
		return (free(oldpwd), perror("getcwd"), 1);
	update_pwd_env(oldpwd, newpwd, &info->my_envp);
	return (free(oldpwd), free(newpwd), 0);
}

// OG
//int	cd_builtin(char **args, t_info *info)
//{
//    char	*oldpwd;
//    char	*newpwd;
//    char	*dir;
////add -
//    if (!args[1])
//        dir = ft_getenv(info->my_envp, "HOME");
//    else if (args[2])
//    {
//        printf("cd: too many arguments\n");
//        return (1);
//    }
//    else
//        dir = args[1];
//    oldpwd = getcwd(NULL, 0);
//    if (oldpwd == NULL)
//    {
//        perror("getcwd");
//        return (errno);
//    }
//    if (chdir(dir) != 0)
//    {
//        perror("cd");
//        free(oldpwd);
//        return (1);
//    }
//    newpwd = getcwd(NULL, 0);
//    if (newpwd == NULL)
//    {
//        perror("getcwd");
//        free(oldpwd);
//        return (errno);
//    }
//    update_env("OLDPWD", oldpwd, &info->my_envp);
//    update_env("PWD", newpwd, &info->my_envp);
//    free(oldpwd);
//    free(newpwd);
//    return (0);
//}
