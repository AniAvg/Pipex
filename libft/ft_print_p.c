/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_p.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anavagya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 16:14:49 by anavagya          #+#    #+#             */
/*   Updated: 2025/03/20 16:14:52 by anavagya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_print_p(void *ptr)
{
	int	len;

	len = 0;
	if (!ptr)
	{
		write(1, "0x0", 3);
		return (3);
	}
	len += write(1, "0x", 2);
	len += ft_print_x((unsigned long)ptr, 'x');
	return (len);
}
