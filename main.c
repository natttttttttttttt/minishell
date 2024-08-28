#include "minishell.h"

int	all_spaces(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if ((str[i] > 8 && str[i] < 14) || str[i] == 32)
			i++;
		else
			return (0);
	}
	return (1);
}

int	parsing(char *str)
{
	if (!str)
		return (0);
	if (str[0] == '\0' || str[0] == '\n')
		return (0);
	if (all_spaces(str))
		return (0);
	return (1);
}





int	main()
{
	char	*input;
	t_token	*token_lst;

	while (1)
	{
		token_lst = NULL;
		input = readline("minishell> ");
		if (parsing(input))
			save_tokens(input, &token_lst);
		print_list(token_lst);
		free(input);
		free_lst(&token_lst);
	}
	return (0);
}