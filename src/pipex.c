/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharumi <naharumi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 19:05:01 by naharumi          #+#    #+#             */
/*   Updated: 2025/01/07 19:05:02 by naharumi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	error(const char *msg)
{
	write(STDERR_FILENO, "\033[31mError: ", 13);
	write(STDERR_FILENO, msg, ft_strlen(msg));
	write(STDERR_FILENO, "\n", 1);
	exit(EXIT_FAILURE);
}

void	free_arr(char **arr)
{
	int	i;

	if (!arr)
		return;
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
	return ;
}

char	*find_path(char *cmd, char **envp)
{
	char	**paths;
	char	*pathname;
	int		i;

	i = 0;
	while (envp[i] && ft_strnstr(envp[i], "PATH=", 5) == NULL)
		i++;
	if (!envp[i])
		error("PATH environment variable not found");
	paths = ft_split(envp[i] + 5, ':');
	i = 0;
	while (paths[i])
	{
		pathname = ft_strdup(paths[i]);
		pathname = ft_strjoin(pathname, "/");
		pathname = ft_strjoin(pathname, cmd);
		if (access(pathname, F_OK | X_OK) == 0)
		{
			free_arr(paths);
			return (pathname);
		}
		free(pathname);
		i++;
	}
	free_arr(paths);
	return (NULL);
}

void	execute(char *argv, char **envp)
{
	char	**cmd;
	char	*path;

	cmd = ft_split(argv, ' ');
	path = find_path(cmd[0], envp);
	printf("path: %s\n", path);
	if (path == NULL)
	{
		free_arr(cmd);
		error("Command not found");
	}
	
	if (execve(path, cmd, envp) == -1)
	{
		free_arr(cmd);
		free(path);
		error("Command execution failed");
	}
}

void	child_process(char **argv, char **envp, int *fd)
{
	int	infile;

	infile = open(argv[1], O_RDONLY, 0777);
	if (infile == -1)
		error("Failed to open input file");
	dup2(fd[1], STDOUT_FILENO);
	dup2(infile, STDIN_FILENO);
	close(fd[0]);
	close(fd[1]);
	close(infile);
	execute(argv[2], envp);
}

void	parent_process(char **argv, char **envp, int *fd)
{
	int	outfile;

	outfile = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (outfile == -1)
		error("Failed to open output file");
	dup2(fd[0], STDIN_FILENO);
	dup2(outfile, STDOUT_FILENO);
	close(fd[0]);
	close(fd[1]);
	close(outfile);
	execute(argv[3], envp);
}

int main(int ac, char **av, char **envp)
{
	int		fd[2];
	pid_t	pid;

	if (ac != 5)
		error("Usage: ./pipex infile cmd1 cmd2 outfile");
	if (pipe(fd) == -1)
		error("Failed to create pipe");
	pid = fork();
	if (pid == -1)
		error("Failed to create child process");
	if (pid == 0)
		child_process(av, envp, fd);
	else
	{
		waitpid(pid, NULL, 0);
		parent_process(av, envp, fd);
	}
	return (0);
}

// https://gitlab.com/madebypixel02/pipex