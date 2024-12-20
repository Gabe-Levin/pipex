/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glevin <glevin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 11:32:11 by glevin            #+#    #+#             */
/*   Updated: 2024/11/13 13:07:47 by glevin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/main_bonus.h"

void	read_here_doc(t_pipex *pipex, int *fd, char *limiter)
{
	char	*line;

	close(fd[0]);
	while (1)
	{
		write(1, "> ", 2);
		line = get_next_line(STDIN_FILENO);
		if (ft_strlen(limiter) == 0)
		{
			if (ft_strncmp(line, "\n", 1) == 0)
			{
				free(line);
				exit_clean(pipex, 0);
			}
		}
		else if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0)
		{
			free(line);
			exit_clean(pipex, 0);
		}
		write(fd[1], line, ft_strlen(line));
		free(line);
	}
}

void	here_doc(t_pipex *pipex, char *limiter, int argc)
{
	pid_t	pid;
	int		fd[2];

	if (argc < 6)
		exit_clean(pipex, 1);
	if (pipe(fd) == 1)
	{
		perror("fork failed");
		exit_clean(pipex, 1);
	}
	pid = fork();
	if (pid == 0)
		read_here_doc(pipex, fd, limiter);
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		wait(NULL);
	}
}
