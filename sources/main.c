/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anavagya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 17:19:22 by anavagya          #+#    #+#             */
/*   Updated: 2025/03/20 17:22:25 by anavagya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

char	*find_path(char **envp)
{
	int	i;

	i = 0;
	while (!(ft_strncmp(envp[i], "PATH", 4)))
		i++;
	return (*envp + 5);
}


int	main(int argc, char **argv, char **envp __attribute__((unused)))
{
	(void)argv;
	if (argc != 5)
		printf("Inch reaktiv eq\n");
	printf("%s\n", find_path(envp));
	return (0);
}
