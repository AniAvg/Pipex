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
	(void)argc;
	pip->in_fd = open(argv[1], O_RDONLY);
	if (pip->in_fd == -1)
		send_err_and_quit("Error opening file");
	pip->out_fd = open(argv[4], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (pip->out_fd == -1)
		send_err_and_quit("Error Opening File");
}

char *find_path(char **envp)
{
	int i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 4))
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

	i = 0;
	if (!path || !cmd)
		return (NULL);
	while (path[i])
	{
		smth = ft_strjoin(path[i], "/");
		command = ft_strjoin(smth, cmd);
		free(smth);
		printf(" res %s\n", command);
		if (access(command, F_OK) == 0)
			return (command);
		free(command);
		i++;
	}
	return (NULL);
}

void	execute_pipeline(t_pipex pip, char **argv, char **envp)
{
	pip.pid1 = fork();
	if (pip.pid1 == -1)
		send_err_and_quit("fork() Failed");
	if (pip.pid1 == 0)
		cmd1_child(pip, argv, envp);
	pip.pid2 = fork();
	if (pip.pid2 == -1)
		send_err_and_quit("fork() Failed");
	if (pip.pid2 == 0)
		cmd2_child(pip, argv, envp);
	close(pip.fd[0]);
	close(pip.fd[1]);
	waitpid(pip.pid1, NULL, 0);
	waitpid(pip.pid2, NULL, 0);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pip;

	(void)argc;
	if (argc != 5)
		send_err_and_quit("Argument Error");
	open_files(argc, argv, &pip);
	if (pipe(pip.fd) == -1)
		send_err_and_quit("pipe() failed");
	pip.env_path = find_path(envp);
	pip.cmd_path = ft_split(pip.env_path, ':');
	execute_pipeline(pip, argv, envp);
	free_array(pip.cmd_path);
	return (0);
}
