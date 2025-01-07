/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharumi <naharumi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 17:59:23 by naharumi          #+#    #+#             */
/*   Updated: 2025/01/07 19:08:50 by naharumi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	print_str(char *str)
{
	int	count;

	if (!str)
		return (print_str("(null)"));
	count = 0;
	while (*str)
	{
		count += print_chr(*str);
		str++;
	}
	return (count);
}

int	print_nbr(long nbr)
{
	int		count;
	char	c;

	count = 0;
	if (nbr < 0)
	{
		count += print_chr('-');
		nbr = -nbr;
	}
	if (nbr >= 10)
	{
		count += print_nbr(nbr / 10);
		count += print_nbr(nbr % 10);
	}
	else
	{
		c = nbr + '0';
		count += print_chr(c);
	}
	return (count);
}

int	print_unbr(unsigned int nbr)
{
	int		count;
	char	c;

	count = 0;
	if (nbr >= 10)
	{
		count += print_nbr(nbr / 10);
		count += print_nbr(nbr % 10);
	}
	else
	{
		c = nbr + '0';
		count += print_chr(c);
	}
	return (count);
}

int	print_ptr(va_list args)
{
	int				count;
	unsigned long	ptr;

	count = 0;
	ptr = va_arg(args, unsigned long);
	if (ptr == 0)
		count += print_str("(nil)");
	else
	{
		count += print_str("0x");
		count += print_hex(ptr, "0123456789abcdef");
	}
	return (count);
}

int	print_hex(unsigned long n, const char *base)
{
	int			count;
	char		c;

	count = 0;
	if (n >= 16)
	{
		count += print_hex(n / 16, base);
		count += print_hex(n % 16, base);
	}
	else
	{
		c = base[n];
		count += print_chr(c);
	}
	return (count);
}
