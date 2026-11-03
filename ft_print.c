/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malquran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/02 09:16:26 by malquran          #+#    #+#             */
/*   Updated: 2026/11/02 09:16:28 by malquran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

// did not normate // restudy vardic functions // redo the whole thing

static int ft_format(char c, va_list args)
{
   if (c == 'c' )
        return (ft_putchar(va_arg(args, int)));
    else if (c == 's')
        return (ft_putstr(va_arg(args, char *)));
    else if (c == 'p')
        return (ft_putptr(va_arg(args, void *)));
    else if (c == 'd' || c == 'i')
        return (ft_putnbr(va_arg(args, int)));
    else if (c == 'u')
        return (ft_putunsigned(va_arg(args, unsigned int)));
    else if (c == 'x' || c == 'X')
        return (ft_puthex(va_arg(args, unsigned int), c));
    else if(c == '%')
        return (ft_putchar('%'));
    return (-1);
}

// did not handile the error // edge cases
int	ft_printf(const char *format, ...)
{
    va_list args;
    int i;
    int count;

    i = 0;
    count = 0;
    va_start(args, format);
    while(format[i])
    {
        if(format[i] == '%')
        {
            i++;
            count += ft_format(format[i], args);
            i++;
        }
        else
        {
        ft_putchar(format[i]);
        i++;
        count++;
        }

    }
    va_end(args);
    return (count);
}