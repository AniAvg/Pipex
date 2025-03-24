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

# include <libft.h>
# include <stdio.h>

typedef struct s_pipex
{
	pid_t	pid1;
	pid_t	pid2;
	int		pipe_fd[2];
	int		file1;
	int		file2;
	char	*env_path;
	char	**cmd_path;
}	t_pipex;

char	*find_path(char **envp);
char	*get_command(char **path, char	*cmd);

#endif
