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

void	free_arr(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
	return ;
}

void	exit_error(char *msg, char *param, char **arr)
{
	ft_putstr_fd("\033[31mError:\033[0m ", 2);
	ft_putstr_fd(msg, 2);
	if (param)
		ft_putstr_fd(param, 2);
	write(STDERR_FILENO, "\n", 1);
	free_arr(arr);
	exit(EXIT_FAILURE);
}

char	**get_paths(char **envp)
{
	char	**paths;
	int		i;

	i = 0;
	while (envp[i] && ft_strnstr(envp[i], "PATH=", 5) == NULL)
		i++;
	if (!envp[i])
		exit_error("PATH environment variable not found", NULL, NULL);
	paths = ft_split(envp[i] + 5, ':');
	return (paths);
}

char	*find_path(char *cmd, char **envp)
{
	char	**paths;
	char	*pathname;
	int		i;

	paths = get_paths(envp);
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
	if (path == NULL)
	{
		exit_error("Command not found: ", cmd[0], cmd);
	}
	if (execve(path, cmd, envp) == -1)
	{
		free_arr(cmd);
		free(path);
		exit_error("Command execution failed: ", cmd[0], cmd);
	}
}

void	child_process(char **argv, char **envp, int *fd)
{
	int	infile;

	infile = open(argv[1], O_RDONLY, 0777);
	if (infile == -1)
		exit_error("Failed to open input file: ", argv[1], NULL);
	if (dup2(fd[1], STDOUT_FILENO) == -1 || dup2(infile, STDIN_FILENO) == -1)
		exit_error("dup2 failed", NULL, NULL);
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
		exit_error("Failed to open output file: ", argv[4], NULL);
	if (dup2(fd[0], STDIN_FILENO) == -1 || dup2(outfile, STDOUT_FILENO) == -1)
		exit_error("dup2 failed", NULL, NULL);
	close(fd[0]);
	close(fd[1]);
	close(outfile);
	execute(argv[3], envp);
}

int	main(int ac, char **av, char **envp)
{
	int		fd[2];
	pid_t	pid;
	int		status;

	if (ac != 5)
		exit_error("Usage: ./pipex infile cmd1 cmd2 outfile", NULL, NULL);
	if (pipe(fd) == -1)
		exit_error("Failed to create pipe", NULL, NULL);
	pid = fork();
	if (pid == -1)
		exit_error("Failed to fork process", NULL, NULL);
	if (pid == 0)
		child_process(av, envp, fd);
	else
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
			exit(EXIT_FAILURE);
		parent_process(av, envp, fd);
	}
}

// valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes ./pipex infile "invalidcmd" "wc -l" outfile
// valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --trace-children=yes