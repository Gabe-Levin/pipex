/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glevin <glevin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 12:12:42 by glevin            #+#    #+#             */
/*   Updated: 2024/10/24 17:44:33 by glevin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/main.h"

typedef struct s_pipex
{
	int		fd[2];
	pid_t	pid1;
	pid_t	pid2;
	char	*cmd;
	char	**cmd_args;
	int		infile;
	int		outfile;

}			t_pipex;

// char	*get_cmd_path(t_pipex *pipex, char **envp, char **argv)
// {
// }

void	create_pipe(t_pipex *pipex, char **envp, char **argv)
{
	if (pipe(pipex->fd) < 0)
		exit(1);
	pipex->pid1 = fork();
	if (pipex->pid1 == -1)
	{
		perror("fork failed");
		exit(1);
	}
	if (pipex->pid1 == 0)
	{
		dup2(pipex->fd[1], STDOUT_FILENO);
		close(pipex->fd[0]);
		close(pipex->fd[1]);
		dup2(pipex->infile, STDIN_FILENO);
		close(pipex->infile);
		pipex->cmd_args = ft_split(argv[2], ' ');
		pipex->cmd = pipex->cmd_args[0];
        
		execve(pipex->cmd, pipex->cmd_args, envp);
	}
	pipex->pid2 = fork();
	if (pipex->pid2 == -1)
	{
		perror("fork failed");
		exit(1);
	}
	if (pipex->pid2 == 0)
	{
		dup2(pipex->fd[0], STDIN_FILENO);
		close(pipex->fd[0]);
		close(pipex->fd[1]);
		dup2(pipex->outfile, STDOUT_FILENO);
		close(pipex->outfile);
		// pipex->cmd = "/usr/bin/wc";
		pipex->cmd_args = ft_split(argv[3], ' ');
		pipex->cmd = pipex->cmd_args[0];
        
		execve(pipex->cmd, pipex->cmd_args, envp);
	}
    close(pipex->fd[0]);
    close(pipex->fd[1]);
    waitpid(pipex->pid1, NULL, 0);
    waitpid(pipex->pid2, NULL, 0);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex pipex;
	if (argc != 5)
		return (1);
    pipex.infile = open(argv[1], O_RDONLY);
    pipex.outfile = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);

    
    create_pipe(&pipex, envp, argv);
	// for (int i = 0; envp[i] != NULL; i++)
	// {
	// 	printf("%s\n", envp[i]);
	// }
	// pipex = NULL;
	argv = NULL;
	envp = NULL;
	return (0);
}

// ./pipex ./infile.txt "/bin/cat" "/usr/bin/wc -l" ./outfile.txt

