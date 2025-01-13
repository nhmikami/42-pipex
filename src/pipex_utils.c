/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharumi <naharumi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 19:05:01 by naharumi          #+#    #+#             */
/*   Updated: 2025/01/09 20:57:24 by naharumi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

/*void	close_fds(void)
{
	int	fd;

	fd = 3;
	while (fd < FILE_MAX)
	{
		close(fd);
		fd++;
	}
}

void	exit_error(char *msg, char *param, char **arr, int *fd)
{
	ft_putstr_fd("\033[31mError:\033[0m ", 2);
	ft_putstr_fd(msg, 2);
	if (param)
		ft_putstr_fd(param, 2);
	write(STDERR_FILENO, "\n", 1);
	if (fd)
	{
		if (fd[0] >= 0)
			close(fd[0]);
		if (fd[1] >= 0)
			close(fd[1]);
	}
	if (arr)
		ft_free_arr(arr);
	exit(EXIT_FAILURE);
}*/

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

static char	**get_paths(char **envp)
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
			ft_free_arr(paths);
			return (pathname);
		}
		free(pathname);
		i++;
	}
	ft_free_arr(paths);
	return (NULL);
}
