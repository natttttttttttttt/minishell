/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pibouill <pibouill@student.42prague.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 13:01:51 by pibouill          #+#    #+#             */
/*   Updated: 2024/10/10 21:16:05 by pibouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/../inc/libft.h"

static int	handle_format(char specifier, va_list arg, int fd)
{
	if (specifier == 'c')
		return (putchar_len_fd(va_arg(arg, int), fd));
	else if (specifier == 's')
		return (putstr_len_fd(va_arg(arg, char *), fd));
	else if (specifier == 'p')
		return (putptr_len_fd((unsigned long long)va_arg(arg, void *), 0, fd));
	else if (specifier == 'd' || specifier == 'i')
		return (put_nbr_u_hex_len_fd(va_arg(arg, int), 10, 0, fd));
	else if (specifier == 'u')
		return (put_nbr_u_hex_len_fd(va_arg(arg, unsigned int), 10, 0, fd));
	else if (specifier == 'x')
		return (put_nbr_u_hex_len_fd(va_arg(arg, unsigned int), 16, 0, fd));
	else if (specifier == 'X')
		return (put_nbr_u_hex_len_fd(va_arg(arg, unsigned int), 16, 1, fd));
	else if (specifier == '%')
		return (putchar_len_fd('%', fd));
	else
		return (-1);
}

int	ft_printf_fd(int fd, const char *format, ...)
{
	va_list	args;
	int		count;

	va_start(args, format);
	count = 0;
	if (format == NULL)
		return (-1);
	while (*format)
	{
		if (*format == '%')
			count += handle_format(*(++format), args, fd);
		else
			count += write(fd, format, 1);
		++format;
	}
	va_end(args);
	return (count);
}
