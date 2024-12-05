/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pibouill <pibouill@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 19:13:29 by pibouill          #+#    #+#             */
/*   Updated: 2024/11/25 19:31:34 by pibouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// commenting the ones that are in my libft for now
// and changin

// void	ft_putstr_fd(int fd, char *s)
// {
// 	if (s == NULL)
// 		return ;
// 	write(fd, s, ft_strlen(s));
// }

// char	*ft_strdup(const char *src)
// {
// 	char	*str;
// 	int		i;
//
// 	if (!src)
// 		return (NULL);
// 	i = 0;
// 	if (src[0] == '\0')
// 		str = malloc(1);
// 	else
// 	{
// 		while (src[i])
// 			i++;
// 		str = malloc((i + 1) * sizeof(char));
// 		i = 0;
// 		while (src[i])
// 		{
// 			str[i] = src[i];
// 			i++;
// 		}
// 	}
// 	str[i] = '\0';
// 	return (str);
// }
//
// int	ft_strlen(const char *str)
// {
// 	int	i;
//
// 	if (str == NULL)
// 		return (0);
// 	i = 0;
// 	while (str[i])
// 		i++;
// 	return (i);
// }

// char	*ft_strchr(char *str, int c)
// {
// 	char	*st;
//
// 	st = (char *)str;
// 	if (c == 0)
// 		return (st + ft_strlen(str));
// 	while (*st)
// 	{
// 		if (*st == (char)c)
// 			return (st);
// 		st++;
// 	}
// 	return (NULL);
// }


// int	ft_isalnum(int c)
// {
// 	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
// 		return (1);
// 	if (c >= '0' && c <= '9')
// 		return (1);
// 	return (0);
// }

int	all_digits(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (str[i] == '\0')
		return (0);
	while (str[i])
	{
		if (str[i] >= '0' && str[i] <= '9')
			i++;
		else
			return (0);
	}
	return (1);
}

void	free_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr && arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

// char	*ft_strjoin(char *s1, const char *s2)
// {
// 	char	*res;
// 	size_t	len;
// 	size_t	i;
// 	size_t	j;
//
// 	i = 0;
// 	j = 0;
//
// 	len = ft_strlen(s1) + ft_strlen(s2);
// 	res = (char *)malloc((len + 1) * sizeof(char));
// 	if (!res)
// 		return (NULL);
// 	while (s1 && s1[i])
// 	{
// 		res[i] = s1[i];
// 		i++;
// 	}
// 	while (s2 && s2[j])
// 	{
// 		res[i + j] = s2[j];
// 		j++;
// 	}
// 	res[i + j] = '\0';
// 	return (res);
// }

// static int	count(const char *str, char c)
// {
// 	int	i;
// 	int	k;
//
// 	i = 0;
// 	k = 0;
// 	while (str[i])
// 	{
// 		if (str[i] != c)
// 		{
// 			k++;
// 			while (str[i] && str[i] != c)
// 				i++;
// 		}
// 		else
// 			i++;
// 	}
// 	return (k);
// }
//
// static void	ft_skip(const char *str, char c, int *i, int *from)
// {
// 	while (str[*i] == c)
// 		(*i)++;
// 	*from = *i;
// 	while (str[*i] != c && str[*i])
// 		(*i)++;
// }
//
// char	**ft_split(const char *s, char c)
// {
// 	int		i;
// 	int		k;
// 	int		j;
// 	int		from;
// 	char	**res;
//
// 	i = 0;
// 	k = 0;
// 	res = (char **)malloc((count(s, c) + 1) * sizeof(char *));
// 	if (!res)
// 		return (NULL);
// 	while (s[i])
// 	{
// 		ft_skip(s, c, &i, &from);
// 		if (from == i)
// 			break ;
// 		res[k] = (char *)malloc((i - from + 1) * sizeof(char));
// 		j = 0;
// 		while (from < i)
// 			res[k][j++] = s[from++];
// 		res[k][j] = '\0';
// 		k++;
// 	}
// 	res[k] = NULL;
// 	return (res);
// }

// int	ft_atoi(char *str)
// {
// 	int	i;
// 	int	n;
// 	int	sign;
//
// 	i = 0;
// 	n = 0;
// 	sign = 1;
// 	while ((str[i] == 32) || (str[i] >= 9 && str[i] <= 13))
// 		i++;
// 	if (str[i] == '+' || str[i] == '-')
// 	{
// 		if (str[i] == '-')
// 			sign *= -1;
// 		i++;
// 	}
// 	while (str[i] != '\0' && (str[i] >= '0' && str[i] <= '9'))
// 	{
// 		n *= 10;
// 		n += str[i] - '0';
// 		i++;
// 	}
// 	return (n * sign);
// }

// int	ft_strncmp(char *str1, char *str2, size_t n)
// {
// 	unsigned char	*s1;
// 	unsigned char	*s2;
//
// 	s1 = (unsigned char *)str1;
// 	s2 = (unsigned char *)str2;
// 	while ((*s1 || *s2) && *s1 == *s2 && n - 1 > 0)
// 	{
// 		n--;
// 		s1++;
// 		s2++;
// 	}
// 	if (n != 0)
// 		return (*s1 - *s2);
// 	return (0);
// }

void ft_strncpy(char *dest, const char *src, int size)
{
	int	i;

	i = 0;
	if (size != 0)
	{
		while (src[i] != '\0' && i < size)
		{
			dest[i] = src[i];
			i++;
		}
		dest[i] = '\0';
	}
}

// char	*ft_substr(char *s, int start, int len)
// {
// 	int		size;
// 	char	*res;
// 	int		i;
//
// 	if (start >= ft_strlen(s))
// 		return (NULL);
// 	size = ft_strlen(s) - start;
// 	if (size < len)
// 		len = size;
// 	res = (char *)malloc((len + 1) * sizeof(char));
// 	if (!s || !res)
// 		return (NULL);
// 	i = 0;
// 	while (i < len)
// 	{
// 		res[i] = s[i + start];
// 		i++;
// 	}
// 	res[i] = '\0';
// 	return (res);
// }

// static int	ft_len(int n)
// {
// 	int	l;
//
// 	l = 1;
// 	if (n < 0)
// 	{
// 		n *= -1;
// 		l++;
// 	}
// 	while (n / 10 > 0)
// 	{
// 		l++;
// 		n = n / 10;
// 	}
// 	return (l);
// }
//
// char	*ft_itoa(int n)
// {
// 	char	*res;
// 	int		l;
//
// 	l = ft_len(n);
// 	res = (char *)malloc((l + 1) * sizeof(char));
// 	if (!res)
// 		return (NULL);
// 	res[l] = '\0';
// 	l--;
// 	while (l >= 0)
// 	{
// 		res[l] = (n % 10) + '0';
// 		n = n / 10;
// 		l--;
// 	}
// 	return (res);
// }

// char	*ft_strrchr(const char *str, int c)
// {
// 	int	l;
//
// 	l = (int)ft_strlen((char *)str);
// 	while (l >= 0)
// 	{
// 		if (str[l] == (char)c)
// 			return ((char *)(str + l));
// 		l--;
// 	}
// 	return (NULL);
// }
