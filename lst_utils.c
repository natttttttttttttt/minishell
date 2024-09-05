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
    t_token *current = head;
    t_token *next_node;

    while (current != NULL) {
        next_node = current->next; // Save the next node
        free(current->txt);        // Free the duplicated string
        free(current);             // Free the current node
        current = next_node;       // Move to the next node
    }
}
void free_command_list(t_cmd *head) {
    t_cmd *current = head;
    t_cmd *next_node;

    while (current != NULL) {
        next_node = current->next; // Save the next node
        
        // Free args
        if (current->args != NULL) {
            char **arg = current->args;
            while (*arg != NULL) {
                free(*arg); // Free each string in the args array
                arg++;
            }
            free(current->args); // Free the args array itself
        }

        // Free other fields
        free(current->input);
        free(current->output);
        free(current->append);
        free(current->delimiter);
        
        free(current); // Free the current node
        current = next_node; // Move to the next node
    }
}
void free_all(t_cmd *cmd, t_token *token)
{
	free_token_lst(token);
	free_command_list(cmd);
}