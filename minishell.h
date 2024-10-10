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

typedef struct s_command
{
	char				**args;
	char				*input;
	char				*output;
	char				*append;
	char				*delimiter;
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
	t_token	*tokens;
	t_cmd	*cmds;
}	t_info;

//list utils
t_token	*lst_create(char *str, t_type type);
t_token	*ft_lstlast(t_token *lst);
void	free_lst(t_token **lst);
void	lst_add_back(t_token **lst, t_token *new);
//libft
char	*ft_itoa(int n);
char	*ft_strchr(char *str, int c);
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
void	save_sep(t_token **lst, char *str, int i, int type);
void	save_word(t_token **lst, char *word, int q);
int		save_tokens(char *str, t_token **lst, t_info *info);
//cmds
t_cmd	*cmd_new(void);
t_cmd	*parse_tokens(t_token *tokens, t_info *info);
void	add_cmd_arg(t_cmd *cmd, char *arg);
void	cmd_to_path(t_cmd *cmd_lst, t_info *info);
void	del_arg(char **args);
void	execute_commands(t_cmd *cmd, t_info *info);
//vars
int		valid_var_name(char *s);
void	vars_to_value(t_token *lst, t_info info);
//builtins
int		is_builtin(t_cmd *cmd);
int		run_builtin(t_cmd *cmd, t_info *info, int fd_out);
int		cd_builtin(char **args, t_info *info);
int		echo_builtin(char **args, int fd_out);
int		env_builtin(char **my_env);
void	exit_builtin(char **args, t_info *info);
int		export_builtin(char **args, t_info *info, int i);
int		pwd_builtin(void);
int		unset_builtin(char **args, t_info *info, int i, int j);
//cleanup
void	free_arr(char **arr);
void	free_command_list(t_cmd *head);
void	free_token_lst(t_token *head);
void	free_all(t_cmd *cmd, t_token *token);
//envp
char	**copy_envp(char **envp);
int		find_env_var(char **my_envp, char *var);
char	*ft_getenv(char **my_envp, char *var);
void	update_env(char *var, char *value, char ***my_envp);
//heredoc
void	heredoc(char *dlmtr);
//debug
void	print_cmd_lst(t_cmd *cmd_lst);
void	print_list(t_token *lst);
#endif