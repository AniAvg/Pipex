/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anavagya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 10:54:39 by anavagya          #+#    #+#             */
/*   Updated: 2025/01/31 16:36:31 by anavagya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t				i;
	unsigned char		*d;
	const unsigned char	*s;

	d = (unsigned char *)dst;
	s = (const unsigned char *)src;
	if (d == 0 && s == 0)
		return (0);
	i = 0;
	while (i < len)
	{
		if (d > s && d < s + len)
			d[(len - 1) - i] = s[(len - 1) - i];
		else
		{
			d[i] = s[i];
		}
		i++;
	}
	return (dst);
}
