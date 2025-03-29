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

void	open_files(int argc, char **argv, t_pipex *pip)
{
	pip->in_fd = open(argv[1], O_RDONLY);
	if (pip->in_fd == -1)
		send_err_and_quit("Error opening file");
	pip->out_fd = open(argv[argc -1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (pip->out_fd == -1)
		send_err_and_quit("Error Opening File");
}

char	*find_path(char **envp)
{
	int	i;

	i = 0;
	if (!envp)
		return (NULL);
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], "PATH", 4))
			return (envp[i] + 5);
		i++;
	}
	return (NULL);
}

char	*get_command(char **path, char	*cmd)
{	
	int		i;
	char	*smth;
	char	*command;

	i = -1;
	if (!path || !cmd)
		return (NULL);
	if (cmd[0] == '/' || (cmd[0] == '.' && cmd[1] == '/'))
	{
		if (access(cmd, F_OK) == 0)
			return (cmd);
		return (NULL);
	}
	while (path[++i])
	{
		smth = ft_strjoin(path[i], "/");
		command = ft_strjoin(smth, cmd);
		free(smth);
		if (access(command, F_OK) == 0)
			return (command);
		free(command);
	}
	printf(" res %s\n", command);
	return (NULL);
}

void	execute_pipeline(t_pipex pipex, char **argv, char **envp)
{
	pipex.pid1 = fork();
	if (pipex.pid1 == -1)
		send_err_and_quit("fork() Failed");
	if (pipex.pid1 == 0)
		cmd1_child(pipex, argv, envp);
	pipex.pid2 = fork();
	if (pipex.pid2 == -1)
		send_err_and_quit("fork() Failed");
	if (pipex.pid2 == 0)
		cmd2_child(pipex, argv, envp);
	close(pipex.fd[0]);
	close(pipex.fd[1]);
	waitpid(pipex.pid1, NULL, 0);
	waitpid(pipex.pid2, NULL, 0);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;

	if (argc != 5)
		send_err_and_quit("Argument Error");
	open_files(argc, argv, &pipex);
	if (pipe(pipex.fd) == -1)
		send_err_and_quit("pipe() failed");
	pipex.env_path = find_path(envp);
	pipex.cmd_path = ft_split(pipex.env_path, ':');
	execute_pipeline(pipex, argv, envp);
	free_array(pipex.cmd_path);
	pipex.cmd_path = NULL;
	close(pipex.in_fd);
	close(pipex.out_fd);
	return (0);
}
