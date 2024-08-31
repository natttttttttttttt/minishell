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
size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}
char	*ft_strchr(char *str, int c)
{
	char	*st;
	
	st = (char *)str;
	if (c == 0)
		return (st + ft_strlen(str));
	while (*st)
	{
		if (*st == (char)c)
			return (st);
		st++;
	}
	return (NULL);
}
char*	ft_strcpy(char *src, int a, int b)
{
	int i;
	char *dest;

	i = 0;
	dest = (char *)malloc(sizeof(char) * (b - a + 2));
	while (a <= b)
		{
			dest[i] = src[a];
			i++;
			a++;
		}
		dest[i] = '\0';
	return (dest);
}
int	ft_isalnum(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}
char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*res;
	size_t	len;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (s1 == NULL)
		len = ft_strlen(s2);
	else
		len = ft_strlen(s1) + ft_strlen(s2);
	res = (char *)malloc((len + 1) * sizeof(char));
	if (!res)
		return (NULL);
	if (s1)
	{	while (s1[i])
		{
			res[i] = s1[i];
			i++;
		}
	}
	while (s2[j])
	{
		res[i + j] = s2[j];
		j++;
	}
	res[i + j] = '\0';
	return (res);
}