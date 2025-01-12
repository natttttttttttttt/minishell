- [x] cmd_to_path.c -> line too long on commented previous functions 

- [ ] cmds.c -> add_cmd_arg() and parse_tokens() => too long functions
    - parse_tokens() is a bitch to norminette
    - add_cmd_arg done

- [x] envp.c -> copy_env() and update_env() => too long

- [x] export_builtins.c -> func too long ->fixed except comments

- [x] heredoc.c -> func too long

- [ ] main.c -> parse_and_exe() => too long bc of the debugging stuff, keeping it for now just in case

- [ ] print_stuff.c -> lots of stuff but ig we dc

- [x] unset_builtin.c -> func too long

---

- cat | ls (any ammount of cat) is broken so pipes were unfortuntely fucked up while norminetting; 
upd: echo hi > out | echo bye >out2 also doesn't work and most of the tests that are failing now are for the same reason (it's something with pipe ends waiting but i can't tell where rn), it was def working before

- test 127 : idk if it's the broken pipes again or it just never worked

- if you give it the name of a file in the current directory (cd src; vars.c) it gets an exec error

- cmd_to_path:250 need to fork for this one, i fixed it somewhere but idk if that commit is lost, will have a look on campus computer 

- guess it's because of that fork too but running ./minishell inside minishell also fails (if you exit once the original one should still run but it just exits alltogether)
this is the working version for these three (it will still fail if you give it src/vars.c but bash also tries to execute it this way so i think it's ok):

``` c
void	cmd_to_path(t_cmd *cmd_lst, t_info *info)
{
	char	*tmp;
	DIR		*dir;
	while (cmd_lst)
	{
		if (cmd_lst->args[0][0] == '\0' && cmd_lst->args[1])
			del_arg(cmd_lst->args);
		if (cmd_lst->args && cmd_lst->args[0][0] != '\0')
		{
			if (!is_builtin(cmd_lst))
			{
				dir = opendir(cmd_lst->args[0]);
				if ((ft_strchr(cmd_lst->args[0], '/'))  && (errno == ENOENT || errno == EACCES))
				{
					if (errno == ENOENT)
						info->exit_code = 127;
					else
						info->exit_code = 126;
					perror(cmd_lst->args[0]);
					free(cmd_lst->args[0]);
					cmd_lst->args[0] = ft_strdup("");
				}
				else if (dir != NULL)
				{
					closedir(dir);
					if (ft_strncmp(cmd_lst->args[0], "./", 2) == 0
						|| ft_strncmp(cmd_lst->args[0], "../", 3) == 0
						|| ft_strncmp(cmd_lst->args[0], "/", 1) == 0)
					{
						printf("%s: is a directory\n", cmd_lst->args[0]);
						info->exit_code = 126;
					}
					else
					{
						printf("%s: command not found\n", cmd_lst->args[0]);
						info->exit_code = 127;
					}
					free(cmd_lst->args[0]);
					cmd_lst->args[0] = ft_strdup("");
				}
				else if ((access(cmd_lst->args[0], F_OK) == 0) && !(ft_strchr(cmd_lst->args[0], '/')))
				{
					printf("%s: command not found\n", cmd_lst->args[0]);
					info->exit_code = 127;
					free(cmd_lst->args[0]);
					cmd_lst->args[0] = ft_strdup("");
				}
				else if (access(cmd_lst->args[0], X_OK) != 0)
				{
					tmp = cmd_lst->args[0];
					cmd_lst->args[0] = get_cmd(info, tmp);
					free(tmp);
				}
			}
		}
		cmd_lst = cmd_lst->next;
	}
}
```

execute_command() norminette was the issue

tester -> 127 now
