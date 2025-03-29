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

void	send_err_and_quit(char *str)
{
	perror(str);
	exit(1);
}

void	cmd1_child(t_pipex pipex, char **argv, char **envp)
{
	if (close(pipex.fd[0]) == -1)
		send_err_and_quit("Close Failed");
	if (dup2(pipex.fd[1], 1) == -1)
		send_err_and_quit("dup2 Failed");
	if (dup2(pipex.in_fd, 0) == -1)
		send_err_and_quit("dup2 Failed");
	if (close(pipex.fd[1]) == -1)
		send_err_and_quit("Close Failed");
	pipex.cmds = ft_split(argv[2], ' ');
	if (access(argv[2], F_OK | X_OK) == 0)
		pipex.pathname = ft_strdup(argv[2]);
	else
		pipex.pathname = get_command(pipex.cmd_path, pipex.cmds[0]);
	if (!pipex.pathname)
	{
		free_array(pipex.cmds);
		send_err_and_quit("Command Not Found");
	}
	execve(pipex.pathname, pipex.cmds, envp);
	free(pipex.pathname);
	free_array(pipex.cmds);
}

void	cmd2_child(t_pipex pipex, char **argv, char **envp)
{
	if (close(pipex.fd[1]) == -1)
		send_err_and_quit("Close Failed");
	if (dup2(pipex.fd[0], 0) == -1)
		send_err_and_quit("dup2 Failed");
	if (dup2(pipex.out_fd, 1) == -1)
		send_err_and_quit("dup2 Failed");
	if (close(pipex.fd[0]) == -1)
		send_err_and_quit("Close Failed");
	pipex.cmds = ft_split(argv[3], ' ');
	if (access(argv[3], F_OK | X_OK) == 0)
		pipex.pathname = ft_strdup(argv[3]);
	else
		pipex.pathname = get_command(pipex.cmd_path, pipex.cmds[0]);
	if (!pipex.pathname)
	{
		free_array(pipex.cmds);
		send_err_and_quit("Command Not Found");
	}
	execve(pipex.pathname, pipex.cmds, envp);
	free(pipex.pathname);
	free_array(pipex.cmds);
}
