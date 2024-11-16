/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pibouill <pibouill@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 11:42:15 by pibouill          #+#    #+#             */
/*   Updated: 2024/10/10 21:16:05 by pibouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

static int	handle_format(char specifier, va_list arg)
{
	if (specifier == 'c')
		return (putchar_len(va_arg(arg, int)));
	else if (specifier == 's')
		return (putstr_len(va_arg(arg, char *)));
	else if (specifier == 'p')
		return (putptr_len((unsigned long long)va_arg(arg, void *), 0));
	else if (specifier == 'd' || specifier == 'i')
		return (put_nbr_u_hex_len(va_arg(arg, int), 10, 0));
	else if (specifier == 'u')
		return (put_nbr_u_hex_len(va_arg(arg, unsigned int), 10, 0));
	else if (specifier == 'x')
		return (put_nbr_u_hex_len(va_arg(arg, unsigned int), 16, 0));
	else if (specifier == 'X')
		return (put_nbr_u_hex_len(va_arg(arg, unsigned int), 16, 1));
	else if (specifier == '%')
		return (putchar_len('%'));
	else
		return (-1);
}

int	ft_printf(const char *format, ...)
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
			count += handle_format(*(++format), args);
		else
			count += write(1, format, 1);
		++format;
	}
	va_end(args);
	return (count);
}
