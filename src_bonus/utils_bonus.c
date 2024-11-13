/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glevin <glevin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 10:40:59 by glevin            #+#    #+#             */
/*   Updated: 2024/11/13 13:28:42 by glevin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/main_bonus.h"

void	exit_clean(t_pipex *pipex, int ecode)
{
	int	i;

	if (!pipex)
		return ;
	if (pipex->paths)
	{
		i = 0;
		while (pipex->paths[i])
		{
			free(pipex->paths[i]);
			i++;
		}
		free(pipex->paths);
	}
	exit(ecode);
}

void	free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
		free(split[i++]);
	free(split);
}

char	*get_cmd_path(char **paths, char *in_cmd)
{
	int		i;
	char	*cmd_path;
	char	*tmp_path;

	i = -1;
	if (!paths || !in_cmd)
	{
		return (NULL);
	}
	if (access(in_cmd, X_OK | F_OK) == 0)
		return (in_cmd);
	while (paths[++i])
	{
		tmp_path = ft_strjoin(paths[i], "/");
		cmd_path = ft_strjoin(tmp_path, in_cmd);
		free(tmp_path);
		if (access(cmd_path, X_OK | F_OK) == 0)
			return (cmd_path);
		free(cmd_path);
	}
	return (NULL);
}

int	open_file(t_pipex *pipex, char *filename, int i)
{
	int	fd;

	fd = 0;
	if (i == 0)
		fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0777);
	if (i == 1)
		fd = open(filename, O_RDONLY);
	else if (i == 2)
		fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		perror("\033[31mError");
		exit_clean(pipex, 1);
	}
	return (fd);
}

void	execute(t_pipex *pipex, char *argv, char **envp)
{
	char	**cmd_args;
	char	*cmd;

	cmd_args = ft_split(argv, ' ');
	cmd = get_cmd_path(pipex->paths, cmd_args[0]);
	if (!cmd)
	{
		perror("Command not found");
		free_split(cmd_args);
		exit_clean(pipex, 127);
	}
	if (execve(cmd, cmd_args, envp) == -1)
	{
		perror("execve failed");
		free(cmd);
		free_split(cmd_args);
		exit_clean(pipex, 127);
	}
}
