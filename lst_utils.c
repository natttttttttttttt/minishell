#include "minishell.h"

t_token	*lst_create(char *str, t_type type)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
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

void lst_add_back(t_token **lst, t_token *new)
{
	t_token *last;

    if (new)
    {
        if (*lst)
        {
            last = ft_lstlast(*lst);
            last->next = new;
            new->prev = last;
        }
        else
            *lst = new;
    }
}
char	*ft_strdup(char *src)
{
	char	*str;
	int		i;

	
    if (!src)
        return NULL;
	i = 0;
	while (src[i])
		i++;
	str = malloc((i + 1) * sizeof(char));
	i = 0;
	while (src[i])
	{
		str[i] = src[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}