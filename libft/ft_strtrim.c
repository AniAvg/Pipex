/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anavagya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 16:00:52 by anavagya          #+#    #+#             */
/*   Updated: 2025/01/29 19:02:06 by anavagya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		j;

	i = 0;
	j = ft_strlen(s1) - 1;
	if (!s1 || !set)
		return (NULL);
	if (*s1 == '\0')
		return (ft_substr(s1, 0, 0));
	while (s1[i] && ft_strchr(set, s1[i]))
		i++;
	while (s1[j] && ft_strrchr(set, s1[j]))
		j--;
	if (i > j)
		return (ft_substr("", 0, 0));
	return (ft_substr(s1, i, j - i + 1));
}
