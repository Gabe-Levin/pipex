/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glevin <glevin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 12:17:39 by glevin            #+#    #+#             */
/*   Updated: 2024/11/13 12:25:12 by glevin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

/* write, close, pipe, access, read, dup, dup2, execve, fork */
/* pid_t datatype it is defined in <sys/types.h> */
# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>

/* malloc, free, exit */
# include <stdlib.h>

/* print */
# include <stdio.h>

/* waitpid, wait */
# include <sys/wait.h>

/* open, unlink */
# include "../masterLib/masterLib.h"
# include <fcntl.h>

typedef struct s_pipex
{
	int		infile;
	int		outfile;
	char	**paths;

}			t_pipex;

void		exit_clean(t_pipex *pipex, int ecode);
char		*get_cmd_path(char **paths, char *in_cmd);
int			open_file(t_pipex *pipex, char *filename, int i);
void		free_split(char **split);
void		here_doc(t_pipex *pipex, char *limiter, int argc);
void		execute(t_pipex *pipex, char *argv, char **envp);

#endif
