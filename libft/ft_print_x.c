/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_x.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anavagya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 16:12:43 by anavagya          #+#    #+#             */
/*   Updated: 2025/03/20 16:13:13 by anavagya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_print_x(unsigned long n, char c)
{
	int	len;

	len = 0;
	if (n >= 16)
		len += ft_print_x(n / 16, c);
	if (n % 16 >= 10 && n % 16 <= 15)
	{
		if (c == 'x')
			len += ft_print_c((n % 16) - 10 + 97);
		else
			len += ft_print_c((n % 16) - 10 + 65);
	}
	else
		len += ft_print_c((n % 16) + '0');
	return (len);
}
