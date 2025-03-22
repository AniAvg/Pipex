/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anavagya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 11:07:31 by anavagya          #+#    #+#             */
/*   Updated: 2025/01/30 19:16:52 by anavagya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(char const *s, char c)
{
	size_t	count;

	count = 0;
	while (*s)
	{
		count++;
		while (*s && *s == c)
			s++;
		if (*s == '\0')
			count--;
		while (*s && *s != c)
			s++;
	}
	return (count);
}

static void	free_array(char ***s, size_t count)
{
	size_t	i;

	i = 0;
	while (i < count)
	{
		free((*s)[i]);
		i++;
	}
	free(*s);
	*s = NULL;
}

static char	*cpy_substr(char const *s, size_t first, size_t last)
{
	size_t		i;
	char		*arr;

	arr = (char *)malloc(sizeof(char) * (last - first + 1));
	if (!arr)
		return (NULL);
	i = 0;
	while (first < last)
	{
		arr[i] = s[first];
		i++;
		first++;
	}
	arr[i] = '\0';
	return (arr);
}

static char	**split_words(char **arr, char const *s, char c)
{
	size_t	i;
	size_t	j;
	size_t	index;

	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			index = i;
			while (s[i] != c && s[i])
				i++;
			arr[j++] = cpy_substr(s, index, i);
			if (!arr[j - 1])
			{
				free_array(&arr, j);
				return (NULL);
			}
		}
		else
			i++;
	}
	arr[j] = NULL;
	return (arr);
}

char	**ft_split(char const *s, char c)
{
	int		count;
	char	**arr;

	count = count_words(s, c);
	if (!s)
		return (NULL);
	arr = (char **)malloc(sizeof(char *) * (count + 1));
	if (!arr)
		return (NULL);
	arr = split_words(arr, s, c);
	return (arr);
}
