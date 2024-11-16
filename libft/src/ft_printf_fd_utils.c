/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_fd_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pibouill <pibouill@student.42prague.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 13:09:23 by pibouill          #+#    #+#             */
/*   Updated: 2024/10/10 21:16:05 by pibouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

int	putchar_len_fd(int c, int fd)
{
	return (write(fd, &c, 1));
}

int	putstr_len_fd(char *str, int fd)
{
	int	count;

	count = 0;
	if (str == NULL)
		return (putstr_len_fd("(null)", fd));
	while (*str)
	{
		count += putchar_len_fd((int)*str, fd);
		str++;
	}
	return (count);
}

int	putptr_len_fd(unsigned long long ptr, int ptr_prefix, int fd)
{
	int		count;
	char	*symbols;

	symbols = "0123456789abcdef";
	count = 0;
	if (ptr == 0)
		return (putstr_len_fd(PTR_NULL, fd));
	else
	{
		if (ptr_prefix == 0)
		{
			count += write(fd, "0x", 2);
			ptr_prefix = 1;
		}
		if (ptr >= 16)
		{
			count += putptr_len_fd(ptr / 16, ptr_prefix, fd);
			ptr %= 16;
		}
		if (ptr < 16)
			count += write(fd, &symbols[ptr], 1);
		return (count);
	}
	return (count);
}

int	put_nbr_u_hex_len_fd(long n, int base, int is_uppercase, int fd)
{
	int		count;
	char	*symbols;

	count = 0;
	if (is_uppercase == 1)
		symbols = "0123456789ABCDEF";
	else
		symbols = "0123456789abcdef";
	if (n < 0)
	{
		write(1, "-", 1);
		return (put_nbr_u_hex_len_fd(-n, base, is_uppercase, fd) + 1);
	}
	else if (n < base)
		return (putchar_len_fd(symbols[n], fd));
	else
	{
		count += put_nbr_u_hex_len_fd((n / base), base, is_uppercase, fd);
		count += put_nbr_u_hex_len_fd((n % base), base, is_uppercase, fd);
		return (count);
	}
}
