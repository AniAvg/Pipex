/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anavagya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 17:16:24 by anavagya          #+#    #+#             */
/*   Updated: 2025/03/20 17:17:59 by anavagya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft.h"
# include <unistd.h>
# include <stdio.h>
# include <sys/wait.h>

typedef struct s_pipex
{
	pid_t	pid1;
	pid_t	pid2;
	int		fd[2];
	int		in_fd;
	int		out_fd;
	char	*env_path;
	char	**cmd_path;
	char	**cmds;
	char	*pathname;
}	t_pipex;

char	*find_path(char **envp);
void	open_files(int argc, char **argv, t_pipex *pipe);
void	send_err_and_quit(char *str);
char	*validate_and_duplicate(char *cmd);
char	*get_command(char **path, char	*cmd);
void	cmd1_child(t_pipex pip, char **argv, char **envp);
void	cmd2_child(t_pipex pip, char **argv, char **envp);
void	execute_pipeline(t_pipex pipex, char **argv, char **envp);
void	free_pipex_cmds(t_pipex *pipex);
void	free_pipex_resources(t_pipex *pipex);
void	free_array(char **arr);

#endif
