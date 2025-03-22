/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anavagya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 17:52:33 by anavagya          #+#    #+#             */
/*   Updated: 2025/03/20 16:15:40 by anavagya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check_spec(char specifier, va_list args)
{
	int	count;

	count = 0;
	if (specifier == 'c')
		count += ft_print_c(va_arg(args, int));
	else if (specifier == 's')
		count += ft_print_s(va_arg(args, char *));
	else if (specifier == 'd' || specifier == 'i')
		count += ft_print_d(va_arg(args, int));
	else if (specifier == 'p')
		count += ft_print_p(va_arg(args, void *));
	else if (specifier == 'u')
		count += ft_print_u(va_arg(args, unsigned int));
	else if (specifier == 'x')
		count += ft_print_x(va_arg(args, unsigned int), specifier);
	else if (specifier == 'X')
		count += ft_print_x(va_arg(args, unsigned int), specifier);
	else if (specifier == '%')
		count += ft_print_c(specifier);
	return (count);
}

int	ft_printf(const char *format, ...)
{
	int		i;
	int		count;
	va_list	args;

	va_start(args, format);
	count = 0;
	i = 0;
	while (format[i])
	{
		if (format[i] == '%')
		{
			i++;
			count += check_spec(format[i], args);
		}
		else
			count += write(1, &format[i], 1);
		i++;
	}
	va_end(args);
	return (count);
}
