#include "minishell.h"

t_token	*lst_create(char *str, t_type type)
{
	t_token	*new;

	new = (t_token *)malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->txt = ft_strdup(str);
	new->type = type;
	new->prev = NULL;
	new->next = NULL;
	return (new);
}

t_token	*ft_lstlast(t_token *lst)
{
	if (lst)
	{
		while (lst->next != NULL)
			lst = lst->next;
	}
	return (lst);
}

void	lst_add_back(t_token **lst, t_token *new)
{
	if (new)
	{
		if (*lst)
		{
			new->prev = ft_lstlast(*lst);
			ft_lstlast(*lst)->next = new;
		}
		else
			*lst = new;
	}
}

void	print_list(t_token *lst)
{
	t_token	*node;

	node = lst;
	while (node->type != DONE)
	{
		printf("%s %i\n", (node->txt), node->type);
		node = node->next;
	}
}

void free_token_lst(t_token *head) {
    t_token *node = head;
    t_token *next;

    while (node != NULL) {
        next = node->next; // Save the next node
        free(node->txt);        // Free the duplicated string
        free(node);             // Free the node node
        node = next;       // Move to the next node
    }
}

void free_command_list(t_cmd *head) {
    t_cmd *node = head;
    t_cmd *next;

    while (node != NULL) {
        next = node->next; // Save the next node
        
        // Free args
        if (node->args != NULL) {
            char **arg = node->args;
            while (*arg != NULL) {
                free(*arg); // Free each string in the args array
                arg++;
            }
            free(node->args); // Free the args array itself
        }

        // Free other fields
        free(node->input);
        free(node->output);
        free(node->append);
        free(node->delimiter);
        
        free(node); // Free the node node
        node = next; // Move to the next node
    }
}

void free_all(t_cmd *cmd, t_token *token)
{
	free_token_lst(token);
	free_command_list(cmd);
}