/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_funct2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anavagya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 11:59:18 by anavagya          #+#    #+#             */
/*   Updated: 2025/04/01 11:59:28 by anavagya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_array(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return ;
	while (arr[i])
	{
		free(arr[i]);
		arr[i] = NULL;
		i++;
	}
	free(arr);
}

void	free_pipex_cmds(t_pipex *pipex)
{
	if (pipex->cmds)
		free_array(pipex->cmds);
	if (pipex->cmd_path)
		free_array(pipex->cmd_path);
}

void	free_pipex_resources(t_pipex *pipex)
{
	if (pipex->pathname)
		free(pipex->pathname);
	if (pipex->cmds)
		free_array(pipex->cmds);
	if (pipex->cmd_path)
		free_array(pipex->cmd_path);
}

void	send_err_and_quit(char *str)
{
	perror(str);
	exit(1);
}
