#include "minishell.h"

char	*ft_strdup(char *src)
{
	char	*str;
	int		i;

	if (!src)
		return (NULL);
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