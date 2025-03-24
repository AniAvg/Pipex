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

void	open_files(int argc, char **argv, t_pipex *pipe)
{
	pipe->file1 = open(argv[1], O_RDONLY);
	pipe->file2 = open(argv[5], ); 
	// sharunakeli
}

char	*find_path(char **envp)
{
	int	i;

	i = 0;
	while (ft_strncmp(envp[i], "PATH", 4))
		i++;
	return (envp[i] + 5);
}

char	*get_command(char **path, char	*cmd)
{	
	int		i;
	char	*smth;//anun@ kpoxem kam el che
	char	*command;

	i = 0;
	while (path[i])
	{
		smth = ft_strjoin(path[i], "/");
		command = ft_strjoin(smth, cmd);
		if (access(command, F_OK) == 1)
			return (command);
		i++;
	}
	return (NULL);
}

int main(int argc, char **argv, char **envp)
{
	int		i;
	t_pipex	pipe;

	i = 0;
	(void)argv;
	if (argc != 5)
		ft_printf("Inch reaktiv eq\n"); //heto kpoxem
	else
	{
		pipe.env_path = find_path(envp);
		pipe.cmd_path = ft_split(pipe.env_path, ':');
		if (pipe.pid1 = fork() != -1)
		{
			
		}
		if (pipe.pid2 = fork() != -1)
		{

		}
		waitpid(pipe.pid1, NULL, 0);
		waitpid(pipe.pid2, NULL, 0);
	}
	return (0);
}
