/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pibouill <pibouill@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 18:05:43 by pibouill          #+#    #+#             */
/*   Updated: 2024/10/10 21:16:05 by pibouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

/*
** Creates new string
** from the application of f function
** to each character of *s
*/

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*new;
	int		i;

	i = 0;
	if (s == NULL)
		return (NULL);
	new = malloc(sizeof(char) * ft_strlen(s) + 1);
	if (new == NULL)
		return (NULL);
	while (s[i])
	{
		new [i] = f(i, s[i]);
		i++;
	}
	new[i] = '\0';
	return (new);
}

// static	char	ft_test(unsigned int i, char c)
// {
// 	(void)i;
// 	return (c + 1);
// }
// int	main(void)
// {
// 	char	str[] = "This is a string.";
// 	printf("%s\n", str);
// 	char	*str_new = ft_strmapi(str, ft_test);
// 	printf("%s\n", str_new);
// 	return (0);
// }
