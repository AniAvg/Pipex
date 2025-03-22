/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anavagya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 18:49:54 by anavagya          #+#    #+#             */
/*   Updated: 2025/02/17 13:01:17 by anavagya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_free_str(char *s1, char *s2)
{
	if (s1)
	{
		free(s1);
		s1 = NULL;
	}
	if (s2)
	{
		free(s2);
		s2 = NULL;
	}
}

char	*ft_read_file(int fd, char *buff)
{
	char	*temp;
	int		byte_read;

	byte_read = 1;
	temp = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!temp)
		return (NULL);
	while (byte_read != 0 && !(ft_gnl_strchr(buff, '\n')))
	{
		byte_read = read(fd, temp, BUFFER_SIZE);
		if (byte_read == -1)
		{
			ft_free_str(buff, temp);
			return (NULL);
		}
		temp[byte_read] = '\0';
		buff = ft_gnl_strjoin(buff, temp);
	}
	ft_free_str(temp, NULL);
	return (buff);
}

char	*ft_get_the_line(char *buff)
{
	char	*line;
	int		i;

	i = 0;
	if (!buff || *buff == '\0')
		return (NULL);
	while (buff[i] && buff[i] != '\n')
		i++;
	if (buff[i] == '\n')
		line = ft_gnl_substr(buff, 0, i + 1);
	else
		line = ft_gnl_substr(buff, 0, i);
	return (line);
}

char	*ft_new_line(char *buff)
{
	char	*line;
	int		i;

	i = 0;
	if (!buff)
		return (NULL);
	while (buff[i] && buff[i] != '\n')
		i++;
	if (!buff[i])
	{
		free(buff);
		buff = NULL;
		return (NULL);
	}
	line = ft_gnl_substr(buff, i + 1, ft_strlen(buff) - i);
	free(buff);
	buff = NULL;
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*buff;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		free(buff);
		buff = NULL;
		return (NULL);
	}
	buff = ft_read_file(fd, buff);
	line = ft_get_the_line(buff);
	buff = ft_new_line(buff);
	return (line);
}
