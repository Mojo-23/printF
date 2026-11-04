/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malquran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/02 01:39:09 by malquran          #+#    #+#             */
/*   Updated: 2026/11/02 02:32:57 by malquran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putchar(char c)
{
	return (write(1, &c, 1));
}

int	ft_putstr(char *s)
{
	int	i;

	i = 0;
	if (!s)
	{
		i = write(1, "(null)", 6);
		return (i);
	}
	while (s[i])
	{
		if (write(1, &s[i], 1) != 1)
			return (-1);
		i++;
	}
	return (i);
}

int	ft_putnbr(int n)
{
	long	num;
	int		count;

	count = 0;
	num = n;
	if (num < 0)
	{
		ft_putchar('-');
		count++;
		num = -num;
	}
	if (num >= 10)
		count += ft_putnbr(num / 10);
	ft_putchar((num % 10) + 48);
	return (count + 1);
}

int	ft_putunsigned(unsigned int n)
{
	int	count;

	count = 0;
	if (n >= 10)
		count += ft_putunsigned((n / 10));
	ft_putchar((n % 10) + 48);
	return (count + 1);
}

int	ft_puthex(unsigned long n, char format)
{
	int		count;
	char	*base;

	count = 0;
	if (format == 'x')
		base = "0123456789abcdef";
	else
		base = "0123456789ABCDEF";
	if (n >= 16)
		count += ft_puthex((n / 16), format);
	ft_putchar(base[n % 16]);
	return (count + 1);
}
