
## NEW

- check export please

- norminette cmd_to_path(too long) and export (just small things) and anything i touched tbh

- quotes need to be completely redone, i'm on it but not sure if i'll finish before leaving

- added different error msgs for different quotes

```
void	save_word(t_token **lst, char *word, int q)
{
	char	*tmp;

	tmp = deal_with_quotes(word, q, 0);
	if (ft_strchr(word, '$') && (q != 1 || (q == 1 && ft_strchr(word, '$') > ft_strrchr(word, '\''))))
		lst_add_back(lst, lst_create(tmp, VAR));
	else
		lst_add_back(lst, lst_create(tmp, WORD));
	free (word);
	free(tmp);
}