/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pibouill <pibouill@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 12:23:39 by pibouill          #+#    #+#             */
/*   Updated: 2024/10/10 21:16:05 by pibouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

/*
** Writes *s to fd with newline
*/

void	ft_putendl_fd(char *s, int fd)
{
	if (s == NULL)
		return ;
	ft_putstr_fd(s, fd);
	ft_putchar_fd('\n', fd);
}

// int	main()
// {
// 	ft_putendl_fd("test", 1);
// 	return (0);
// }
