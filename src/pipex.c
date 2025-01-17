/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharumi <naharumi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 19:05:01 by naharumi          #+#    #+#             */
/*   Updated: 2025/01/09 20:57:24 by naharumi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

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

static void	process_child(char **av, char **envp, int *fd)
{
	int	infile;

	close(fd[0]);
	infile = open(av[1], O_RDONLY, 0777);
	if (infile == -1)
	{
		close(fd[1]);
		exit_error("Failed to open input file: ", av[1], NULL);
	}
	if (dup2(fd[1], STDOUT_FILENO) == -1 || dup2(infile, STDIN_FILENO) == -1)
	{
		close(fd[1]);
		close(infile);
		exit_error("dup2 failed", NULL, NULL);
	}
	close(fd[1]);
	close(infile);
	execute(av[2], envp);
}

static void	process_parent(char **av, char **envp, int *fd)
{
	int	outfile;

	outfile = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (outfile == -1)
	{
		close(fd[0]);
		exit_error("Failed to open output file: ", av[4], NULL);
	}
	if (dup2(fd[0], STDIN_FILENO) == -1 || dup2(outfile, STDOUT_FILENO) == -1)
	{
		close(fd[0]);
		close(outfile);
		exit_error("dup2 failed", NULL, NULL);
	}
	close(fd[0]);
	close(outfile);
	execute(av[3], envp);
}

int	main(int ac, char **av, char **envp)
{
	pid_t	pid;
	int		fd[2];
	int		status;

	if (ac != 5)
		exit_error("Usage: ./pipex infile cmd1 cmd2 outfile", NULL, NULL);
	if (pipe(fd) == -1)
		exit_error("Failed to create pipe", NULL, NULL);
	pid = fork();
	if (pid == -1)
		exit_error("Failed to fork process", NULL, NULL);
	if (pid == 0)
		process_child(av, envp, fd);
	else
	{
		close(fd[1]);
		waitpid(pid, &status, 0);
		if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
		{
			close(fd[0]);
			exit(EXIT_FAILURE);
		}
		process_parent(av, envp, fd);
	}
}
