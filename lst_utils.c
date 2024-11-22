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

void	free_token_lst(t_token *head)
{
	t_token	*node;
	t_token	*next;

	node = head;
	while (node != NULL)
	{
		next = node->next;
		free(node->txt);
		free(node);
		node = next;
	}
}

void	free_order(t_order *order)
{
	if(order->input)
		free(order->input);
	if(order->output)
		free(order->output);
	if(order->heredoc)
		free(order->heredoc);
	if(order->append)
		free(order->append);
}

void	free_command_list(t_cmd *head)
{
	t_cmd	*node;
	t_cmd	*next;

	node = head;
	while (node != NULL)
	{
		next = node->next;
		free_arr(node->args);
		free_arr(node->output);
		free_arr(node->input);
		free_arr(node->append);
		free_arr(node->delimiter);
		free_order(node->order);
		free(node->order);
		free(node);
		node = next;
	}
}

void	del_arg(char **args)
{
	int	i;

	if (args == NULL || args[0] == NULL)
		return ;
	free(args[0]);
	i = 0;
	while (args[i] != NULL)
	{
		args[i] = args[i + 1];
		i++;
	}
}