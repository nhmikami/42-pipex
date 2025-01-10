/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharumi <naharumi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 19:05:11 by naharumi          #+#    #+#             */
/*   Updated: 2025/01/09 18:10:55 by naharumi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <fcntl.h> //open
# include <stdio.h> //perror
# include <stdlib.h> //malloc, exit
# include <sys/types.h> //pid_t
# include <sys/wait.h> //wait
# include <unistd.h> //pipe, dup, access, execve, fork
# include "../libft/libft.h"

enum e_pipex_error
{
	END = 1,
	CMD_NOT_FOUND = 0,
	NO_FILE = -1,
	NO_PERM = -2,
	INV_ARGS = -3,
	NO_MEMORY = -4,
	PIPE_ERR = -5,
	DUP_ERR = -6,
	FORK_ERR = -7,
	NO_PATH = -8,
	CMD_FAIL = -9
};

typedef struct s_pipex
{
	int		infile;
	int		outfile;
	int		**pipe;
	int		pipe_count;
	char	**cmds;
	int		cmd_count;
	char	**paths;
	char	*pathname;
	pid_t	pid;
	int		status;
	int		error_log;
}   t_pipex;

#endif