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

# define FILE_MAX 1024

# include <fcntl.h> //open
# include <stdio.h> //perror
# include <stdlib.h> //malloc, exit
# include <sys/types.h> //pid_t
# include <sys/wait.h> //wait
# include <unistd.h> //pipe, dup, access, execve, fork
# include "../libft/libft.h"

int		open_file(char *av, int mode);
void	exit_error(char *msg, char *param, char **arr);
void	setup_io(int ac, char **av, int *infile, int *outfile);
void	execute(char *av, char **envp);
void	here_doc(char **av, int *outfile);

#endif