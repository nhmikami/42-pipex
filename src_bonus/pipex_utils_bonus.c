/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharumi <naharumi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 14:28:18 by naharumi          #+#    #+#             */
/*   Updated: 2025/01/14 14:28:18 by naharumi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

void	exit_error(char *msg, char *param, char **arr)
{
	ft_putstr_fd("\033[31mError:\033[0m ", 2);
	ft_putstr_fd(msg, 2);
	if (param)
		ft_putstr_fd(param, 2);
	write(STDERR_FILENO, "\n", 1);
	if (arr)
		ft_free_arr(arr);
	exit(EXIT_FAILURE);
}

int	open_file(char *av, int mode)
{
	int	file;

	file = 0;
	if (mode == 0)
		file = open(av, O_WRONLY | O_CREAT | O_APPEND, 0777);
	else if (mode == 1)
		file = open(av, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	else if (mode == 2)
		file = open(av, O_RDONLY, 0777);
	if (file == -1)
		exit_error("Failed to open file: ", av, NULL);
	return (file);
}

void	setup_io(int ac, char **av, int *infile, int *outfile)
{
	if (ft_strncmp(av[1], "here_doc", 8) == 0)
	{
		if (ac < 6)
			exit_error(
				"Usage: ./pipex here_doc LIMITER cmd1 cmd2 ... [cmdN] outfile",
				NULL, NULL);
		*outfile = open_file(av[ac - 1], 0);
		here_doc(av, outfile);
	}
	else
	{
		if (ac < 5)
			exit_error("Usage: ./pipex infile cmd1 cmd2 ... [cmdN] outfile",
				NULL, NULL);
		*infile = open_file(av[1], 2);
		*outfile = open_file(av[ac - 1], 1);
		dup2(*infile, STDIN_FILENO);
		close(*infile);
	}
}
