/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharumi <naharumi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 19:05:01 by naharumi          #+#    #+#             */
/*   Updated: 2025/01/09 20:57:24 by naharumi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

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

static char	*find_path(char *cmd, char **envp)
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

void	execute(char *av, char **envp)
{
	char	**cmd;
	char	*path;

	cmd = ft_split_args(av, ' ');
	path = find_path(cmd[0], envp);
	if (path == NULL)
	{
		exit_error("Command not found: ", cmd[0], cmd);
	}
	if (execve(path, cmd, envp) == -1)
	{
		free(path);
		exit_error("Command execution failed: ", cmd[0], cmd);
	}
	free(path);
	ft_free_arr(cmd);
}
