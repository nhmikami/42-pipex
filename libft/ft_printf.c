/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharumi <naharumi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 14:55:30 by naharumi          #+#    #+#             */
/*   Updated: 2025/01/07 19:08:44 by naharumi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	print_chr(char c)
{
	write(1, &c, 1);
	return (1);
}

int	print_arg(va_list args, char spec)
{
	int	count;

	count = 0;
	if (spec == 'c')
		count += print_chr(va_arg(args, int));
	else if (spec == 's')
		count += print_str(va_arg(args, char *));
	else if (spec == 'p')
		count += print_ptr(args);
	else if (spec == 'd' || spec == 'i')
		count += print_nbr(va_arg(args, int));
	else if (spec == 'u')
		count += print_unbr(va_arg(args, unsigned int));
	else if (spec == 'x')
		count += print_hex(va_arg(args, unsigned int), "0123456789abcdef");
	else if (spec == 'X')
		count += print_hex(va_arg(args, unsigned int), "0123456789ABCDEF");
	else if (spec == '%')
		count += print_chr('%');
	return (count);
}

int	ft_printf(const char *format, ...)
{
	int		count;
	va_list	args;

	if (!format)
		return (-1);
	count = 0;
	va_start(args, format);
	while (*format)
	{
		if (*format == '%')
		{
			format++;
			count += print_arg(args, *format);
			format++;
		}
		else
		{
			count += print_chr(*format);
			format++;
		}
	}
	va_end(args);
	return (count);
}
