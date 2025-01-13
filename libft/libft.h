/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharumi <naharumi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 15:05:14 by naharumi          #+#    #+#             */
/*   Updated: 2025/01/06 16:22:24 by naharumi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>

// libft
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strchr(const char *s, int c);
char	*ft_strdup(const char *s);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strnstr(const char *big, const char *little, size_t len);
void	ft_free_arr(char **arr);
void	ft_putchar_fd(char c, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putstr_fd(char *s, int fd);
void	*ft_memmove(void *dest, const void *src, size_t n);
size_t	ft_strlen(const char *s);

// split
char	**ft_split(char const *s, char c);
char	**ft_split_args(char const *s, char c);
char	*get_substr(char const *s, char c);
void	*free_arr(char **arr, int i);
int		args_count(char const *s, char c);
int		arg_len(char const *str, char c);

// get_next_line
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

char	*get_next_line(int fd);

#endif