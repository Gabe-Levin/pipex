/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glevin <glevin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 12:17:39 by glevin            #+#    #+#             */
/*   Updated: 2024/11/10 15:16:24 by glevin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX
# define PIPEX

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
int			openfile(char *filename, int i);
void		free_split(char **split);

#endif
