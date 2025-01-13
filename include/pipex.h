/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharumi <naharumi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 19:05:11 by naharumi          #+#    #+#             */
/*   Updated: 2025/01/09 19:42:17 by naharumi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# define FILE_MAX 1024

# include <fcntl.h> //open
# include <stdio.h> //perror
# include <stdlib.h> //malloc, exit
# include <sys/types.h> //pid_t
# include <sys/wait.h> //wait
# include <unistd.h> //pipe, dup, access, execve, fork
# include "../libft/libft.h"

char	*find_path(char *cmd, char **envp);
void	exit_error(char *msg, char *param, char **arr);

#endif