/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharumi <naharumi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 19:05:01 by naharumi          #+#    #+#             */
/*   Updated: 2025/01/09 18:14:03 by naharumi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

void	process_parent(int *fd, pid_t pid, int *outfile)
{
	int	status;

	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
	{
		close(*outfile);
		exit(EXIT_FAILURE);
	}
}

void	process_child(char *cmd, char **envp, int *outfile)
{
	pid_t	pid;
	int		fd[2];

	if (pipe(fd) == -1)
		exit_error("Failed to create pipe", NULL, NULL);
	pid = fork();
	if (pid == -1)
		exit_error("Failed to fork process", NULL, NULL);
	if (pid == 0)
	{
		close(fd[0]);
		close(*outfile);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		execute(cmd, envp);
	}
	else
		process_parent(fd, pid, outfile);
}

void	here_doc_input(char *limiter, int *fd)
{
	char	*line;

	line = get_next_line(0);
	while (line)
	{
		if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0
			&& line[ft_strlen(limiter)] == '\n')
		{
			free(line);
			close(fd[1]);
			exit(EXIT_SUCCESS);
		}
		ft_putstr_fd(line, fd[1]);
		free(line);
		line = get_next_line(0);
	}
	free(line);
	close(fd[1]);
	exit(EXIT_SUCCESS);
}

void	here_doc(char **av, int *outfile)
{
	pid_t	pid;
	int		fd[2];

	if (pipe(fd) == -1)
		exit_error("Failed to create pipe", NULL, NULL);
	pid = fork();
	if (pid == -1)
		exit_error("Failed to fork process", NULL, NULL);
	if (pid == 0)
	{
		close(fd[0]);
		close(*outfile);
		here_doc_input(av[2], fd);
	}
	else
		process_parent(fd, pid, outfile);
}

int	main(int ac, char **av, char **envp)
{
	int	i;
	int	infile;
	int	outfile;

	setup_io(ac, av, &infile, &outfile);
	if (ft_strncmp(av[1], "here_doc", ft_strlen("here_doc")) == 0)
		i = 3;
	else
		i = 2;
	while (i < ac - 2)
	{
		process_child(av[i], envp, &outfile);
		i++;
	}
	dup2(outfile, STDOUT_FILENO);
	close(outfile);
	execute(av[ac - 2], envp);
	return (0);
}
