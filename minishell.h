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

typedef struct s_token
{
	char			*txt;
	t_type			type;
	struct s_token	*prev;
	struct s_token	*next;
}	t_token;


t_token	*ft_lstlast(t_token *lst);

char	*ft_strdup(char *src);
void	free_lst(t_token **lst);
t_token	*lst_create(char *str, t_type type);
void	lst_add_back(t_token **lst, t_token *new);
char	*ft_strdup(char *src);
void	print_list(t_token *lst);

int		not_words(char *str, int i);
void	save_word(t_token **lst, char *str, int i, int start);
void	save_sep(t_token **lst, char *str, int i, int type);
void	save_tokens(char *str, t_token **lst);

#endif