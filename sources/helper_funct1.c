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

#include "pipex.h"

char	*validate_and_duplicate(char *cmd)
{
	char	*command;

	if (access(cmd, F_OK | X_OK) == 0)
	{
		command = ft_strdup(cmd);
		if (!command)
			send_err_and_quit("strdup() Failed");
		return (command);
	}
	return (NULL);
}

char	*get_command(char **path, char	*cmd)
{	
	int		i;
	char	*smth;
	char	*command;

	i = 0;
	if (!path || !cmd)
		return (NULL);
	if (cmd[0] == '/' || (cmd[0] == '.' && cmd[1] == '/'))
		return (validate_and_duplicate(cmd));
	while (path[i])
	{
		smth = ft_strjoin(path[i], "/");
		command = ft_strjoin(smth, cmd);
		free(smth);
		if (access(command, F_OK) == 0)
			return (command);
		free(command);
		i++;
	}
	return (NULL);
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
		free_pipex_cmds(&pipex);
		send_err_and_quit("Error");
	}
	if (execve(pipex.pathname, pipex.cmds, envp) == -1)
	{
		free_pipex_resources(&pipex);
		send_err_and_quit("execve() Failed");
	}
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
		free_pipex_cmds(&pipex);
		send_err_and_quit("Command Not Found");
	}
	if (execve(pipex.pathname, pipex.cmds, envp) == -1)
	{
		free_pipex_resources(&pipex);
		send_err_and_quit("execve() Failed");
	}
	free(pipex.pathname);
	free_array(pipex.cmds);
}
