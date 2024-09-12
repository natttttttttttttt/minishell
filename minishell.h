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
	int					builtin;
	struct s_command	*next;
	struct s_command	*prev;
}	t_cmd;

typedef struct s_info
{
	char	*input;
	char	*env_path;
	char	**my_envp;
	char	**paths;
}	t_info;

t_token	*ft_lstlast(t_token *lst);
void execute_commands(t_cmd *cmd, t_info *info);
void cmd_to_path(t_cmd *cmd_lst, t_info info);
char	*ft_strdup(char *src);
void	free_lst(t_token **lst);
t_token	*lst_create(char *str, t_type type);
void	lst_add_back(t_token **lst, t_token *new);
void	print_list(t_token *lst);
char	*ft_strchr(char *str, int c);
int	ft_strlen(const char *str);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strabcpy(char *src, int a, int b);
int		ft_isalnum(int c);
char	*copy_word(char *str, int i, int start);
int		not_words(char *str, int i);
void	save_word(t_token **lst, char *word, int q);
void	save_sep(t_token **lst, char *str, int i, int type);
void	save_tokens(char *str, t_token **lst);
void add_cmd_arg(t_cmd *cmd, char *arg);
t_cmd *parse_tokens(t_token *tokens) ;
t_cmd *cmd_new();
char	**ft_split(const char *s, char c);
void	free_arr(char **arr);

void free_command_list(t_cmd *head);
void free_token_lst(t_token *head);
void free_all(t_cmd *cmd, t_token *token);
void pwd_builtin();
int is_builtin(t_cmd *cmd);
void cd_builtin(char **args, t_info *info);
void exit_builtin(char **args);
int	all_digits(char *str);
int	ft_atoi(char *str);
void run_builtin(t_cmd *cmd, t_info *info, int fd_out);
char **copy_envp(char **envp);
int	ft_strncmp(char *str1, char *str2, size_t n);
char *ft_getenv(char **my_envp, char *var);
void update_env(char *var, char *value, char ***my_envp);
void builtin_env(char **my_env);
void export_builtin(char **args, t_info *info);
void ft_strncpy(char *dest, char *src, int size);
void unset_builtin(char **args, t_info *info, int i, int j);
int find_env_var(char **my_envp, char *var);
void echo_builtin(char **args, int fd_out);
#endif