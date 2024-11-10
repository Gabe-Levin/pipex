/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glevin <glevin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 12:12:42 by glevin            #+#    #+#             */
/*   Updated: 2024/11/10 16:55:55 by glevin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/main.h"

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

void	do_pipe(t_pipex *pipex, char **envp, char *argv)
{
	int		status;
	pid_t	pid;
	int		fd[2];

	status = 0;
	if (pipe(fd) < 0)
		exit_clean(pipex, 1);
	pid = fork();
	if (pid == -1)
	{
		perror("fork failed");
		exit_clean(pipex, 1);
	}
	else if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		execute(pipex, argv, envp);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
	}
}

void	init_pipex(t_pipex *pipex, int argc, char **argv, char **envp)
{
	char	*paths;

	pipex->infile = openfile(argv[1], 1);
	pipex->outfile = openfile(argv[argc - 1], 2);
	while (ft_strncmp("PATH", *envp, 4))
		envp++;
	paths = *envp + 5;
	pipex->paths = ft_split(paths, ':');
}

void	set_paths(t_pipex *pipex, char **envp)
{
	char	*paths;

	while (ft_strncmp("PATH", *envp, 4))
		envp++;
	paths = *envp + 5;
	pipex->paths = ft_split(paths, ':');
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;
	int		i;
	int		status;

	if (argc < 5)
		return (1);
	init_pipex(&pipex, argc, argv, envp);
	dup2(pipex.infile, 0);
	i = 2;
	while (i < argc - 2)
		do_pipe(&pipex, envp, argv[i++]);
	dup2(pipex.outfile, STDOUT_FILENO);
	execute(&pipex, argv[argc - 2], envp);
	while (wait(&status) > 0)
	{
		exit_clean(&pipex, 0);
	}
	return (0);
}

// ./pipex ./infile.txt "/bin/cat" "/usr/bin/wc -l" ./outfile.txt
// ./pipex ./infile.txt "/bin/cat" "/usr/bin/wc -l" "/usr/bin/wc
//	-l" ./outfile.txt
//  valgrind --leak-check=full --show-leak-kinds=all ./pipex ./infile.txt "/bin/cat" "/usr/bin/wc
//	-l" "/usr/bin/wc -l" ./outfile.txt

//<infile.txt cat | wc -l | wc -l  > outfile.txt

// glevin@c3a7c2:~/0_projects/pipex$ < ./infile.txt cat | wc -l > ./outfile.txt