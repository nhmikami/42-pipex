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

# include <fcntl.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
# include "../libft/libft.h"

void	execute(char *av, char **envp);
void	here_doc(char **av, int *outfile);
void	setup_io(int ac, char **av, int *infile, int *outfile);
void	exit_error(char *msg, char *param, char **arr);
int		open_file(char *av, int mode);

#endif