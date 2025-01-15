/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pibouill <pibouill@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 13:34:38 by pibouill          #+#    #+#             */
/*   Updated: 2025/01/14 14:39:08 by pibouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <errno.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <limits.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <dirent.h>
# include "../libft/inc/libft.h"

typedef enum e_type
{
	WORD = 1,
	SPACES,
	PIPE,
	INPUT,
	OUTPUT,
	APPEND,
	HEREDOC,
	VAR,
	DONE
}	t_type;

typedef enum e_builtin
{
	BUILTIN_PWD = 1,
	BUILTIN_CD,
	BUILTIN_ECHO,
	BUILTIN_EXIT,
	BUILTIN_ENV,
	BUILTIN_UNSET,
	BUILTIN_EXPORT
}	t_builtin;

typedef struct s_token
{
	char			*txt;
	t_type			type;
	struct s_token	*prev;
	struct s_token	*next;
}	t_token;

typedef struct s_order
{
	char			*input;
	char			*output;
	char			*append;
	char			*heredoc;
	int				i_input;
	int				i_output;
	int				i_append;
	int				count;
	int				i;
}	t_order;

typedef struct s_command
{
	char				**args;
	char				**input;
	char				**output;
	char				**append;
	char				**delimiter;
	t_order				*order;
	struct s_command	*next;
	struct s_command	*prev;
}	t_cmd;

typedef struct s_info
{
	char	*input;
	char	*env_path;
	char	**my_envp;
	char	**paths;
	int		exit_code;
	int		err;
	t_token	*tokens;
	t_cmd	*cmds;
	int		status;
	int		i;
}	t_info;

typedef struct	s_exec_info
{
	int		pipe_fd[2];
	pid_t	pid;
	int		fd[2];
}				t_exec_info;

//list utils
t_token	*lst_create(char *str, t_type type);
t_token	*ft_lstlast(t_token *lst);
void	free_lst(t_token **lst);
void	lst_add_back(t_token **lst, t_token *new);
//libft
char	*ft_itoa(int n);
char	*ft_strchr(const char *str, int c);
char	*ft_strdup(const char *src);
char	*ft_strjoin(char *s1, const char *s2);
char	*ft_strrchr(const char *str, int c);
char	*ft_substr(char *s, int start, int len);
char	**ft_split(const char *s, char c);
int		all_digits(char *str);
int		ft_atoi(char *str);
int		ft_isalnum(int c);
int		ft_strlen(const char *str);
int		ft_strncmp(char *str1, char *str2, size_t n);
void	ft_strncpy(char *dest, const char *src, int size);
//parsing
char	*copy_word(char *str, int i, int start);
int		not_words(char *str, int i);
void	handle_separator(char *str, int *i, int *quotes, t_token **lst);
void	finalize_tokens(char *str, int *i, int quotes, t_token **lst);
void	save_word(t_token **lst, char *word, int q);
int		save_tokens(char *str, t_token **lst, t_info *info);
char	*deal_with_quotes(char *s, int q, int i);
//exe
void	ft_wait(pid_t pid, int status, t_info *info);
int		set_redirs(t_cmd *cmd, t_info *info, int fd[2]);
void	exe_input(int *fd_in, char *str, int *exit_code, int *status);
void	exe_heredoc(char **str, t_info *info, int *fd_in, int *status);
void	exe_output(int *fd_out, char *str, int *exit_code, int *status);
void	exe_append(int *fd_out, char *str, int *exit_code, int *status);
int		exe_pipe(int pipe_fd[2], int fd[2], t_cmd *cmd);
void	prepare_exe(t_cmd *cmd, int status, t_info *info, int fd[2]);
void	ft_execve(t_cmd *cmd, t_info *info, int pipe_fd[2]);
/*void	execute_commands(t_cmd *cmd, t_info *info, int status, int i);*/
void	execute_commands(t_cmd *cmd, t_info *info);
//cmds
int		find_heredoc(t_token *token);
void	fix_order(char **s, int *i);
t_cmd	*cmd_new(void);
t_cmd	*parse_tokens(t_token *tokens, t_info *info);
void	add_cmd_arg(char ***arr, char *arg);
void	cmd_to_path(t_cmd *cmd_lst, t_info *info);
void	del_arg(char **args);
//vars
int		valid_var_name(char *s);
char	*replace_env_vars(const char *txt, t_info info, int i, int start);
char	*extract_variable(const char *txt, int *i);
char	*append_env_value(char *s, char **env_val, int f);
char	*append_substring(char *s, const char *txt, int start, int end);

void	vars_to_value(t_token *lst, t_info info);
//builtins
int		is_builtin(t_cmd *cmd);
int		run_builtin(t_cmd *cmd, t_info *info, int fd_out);
int		cd_builtin(char **args, t_info *info);
int		echo_builtin(char **args, int fd_out);
int		env_builtin(char **my_env, int fd_out);
void	exit_builtin(char **args, t_info *info);
int		export_builtin(char **args, t_info *info, int i);
int		pwd_builtin(void);
int		unset_builtin(char **args, t_info *info, int i, int j);
void	handle_not_builtin(t_cmd *cmd_lst, t_info *info);
char	*get_cmd(t_info *info, char *cmd);
//cleanup
void	free_arr(char **arr);
void	free_command_list(t_cmd **head);
void	free_token_lst(t_token *head);
void	free_before_exit(t_info *info);
void	free_order(t_order *order);
//envp
char	**copy_envp(char **envp);
int		find_env_var(char **my_envp, char *var);
char	*ft_getenv(char **my_envp, char *var);
void	update_env(char *var, char *value, char ***my_envp);
//heredoc
void	heredoc(char **dlmtr, t_info info);

void	ft_signal_handler(int signal);
//debug (DELETE later)
void	print_command(t_cmd *cmd);
void	print_list(t_token *lst);
void	print_order(t_order *order);

// signal
void	setup_signals(void);
void	ft_signal_handler(int signal);
void	sig_handl_child(int signal);

// utils
int		parsing_ok(char *str);
void	syntax_error(int check, t_info *info);

// token utils
void	tkn_input(t_token **tokens, t_info *info, t_cmd **cmd, int *i);
void	tkn_output(t_token **tokens, t_info *info, t_cmd **cmd, int *i);
void	tkn_append(t_token **tokens, t_info *info, t_cmd **cmd, int *i);
void	tkn_heredoc(t_token **tokens, t_info *info, t_cmd **cmd, int *i);
void	tkn_pipe(t_token **tokens, t_info *info, t_cmd **cmd, int *i);

#endif
