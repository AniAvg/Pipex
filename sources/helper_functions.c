/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anavagya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 12:35:08 by anavagya          #+#    #+#             */
/*   Updated: 2025/03/25 12:35:14 by anavagya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

void	free_array(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
}

void	send_err_and_quit(char *str)
{
	perror(str);
	exit(1);
}

void	cmd1_child(t_pipex pip, char **argv, char **envp)
{
	if (close(pip.fd[0]) == -1)
		send_err_and_quit("Close Failed");
	if (dup2(pip.fd[1], 1) == -1)
		send_err_and_quit("dup2 Failed");
	if (dup2(pip.in_fd, 0) == -1)
		send_err_and_quit("dup2 Failed");
	if (close(pip.fd[1]) == -1)
		send_err_and_quit("Close Failed");
	pip.cmds = ft_split(argv[2], ' ');
	pip.pathname = get_command(pip.cmd_path, pip.cmds[0]);
	if (!pip.pathname)
	{
		free(pip.cmds);
		send_err_and_quit("Command Not Found");
	}
	execve(pip.pathname, pip.cmds, envp);
}

void	cmd2_child(t_pipex pip, char **argv, char **envp)
{
	if (close(pip.fd[1]) == -1)
		send_err_and_quit("Close Failed");
	if (dup2(pip.fd[0], 0) == -1)
		send_err_and_quit("dup2 Failed");
	if (dup2(pip.out_fd, 1) == -1)
		send_err_and_quit("dup2 Failed");
	if (close(pip.fd[0]) == -1)
		send_err_and_quit("Close Failed");
	pip.cmds = ft_split(argv[3], ' ');
	pip.pathname = get_command(pip.cmd_path, pip.cmds[0]);
	if (!pip.pathname)
	{
		free(pip.cmds);
		send_err_and_quit("Command Not Found");
	}
	execve(pip.pathname, pip.cmds, envp);
}
