/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharumi <naharumi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 18:37:51 by naharumi          #+#    #+#             */
/*   Updated: 2025/01/06 16:22:24 by naharumi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

static void	*free_arr(char **arr, int i)
{
	int	index;

	index = 0;
	while (index < i)
	{
		free(arr[index]);
		index++;
	}
	free(arr);
	return (NULL);
}

size_t	substr_len(char const *str)
{
	size_t	len;

	len = 0;
	if (str[len] == '\'')
	{
		len++;
		while (str[len] && str[len] != '\'')
			len++;
		len++;
	}
	else if (str[len] == '\"')
	{
		len++;
		while (str[len] && str[len] != '\"')
			len++;
		len++;
	}
	return (len);
}

size_t	arg_len(char const *str, char c)
{
	size_t	len;

	len = 0;
	while (str[len] && str[len] != c)
	{
		if (str[len] == '\'' || str[len] == '\"')
			len += substr_len(&str[len]);
		len++;
	}
	return (len);
}

static char	*get_substr(char const *s, char c)
{
	int		i;
	int		len;
	char	*str;

	len = arg_len(s, c);
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (len > 0)
	{
		if (*s == '\'' || *s == '\"')
		{
			s++;
			len--;
		}
		else
		{
			str[i] = *s;
			s++;
			i++;
			len--;
		}
	}
	str[i] = 0;
	return (str);
}

int	args_count(char const *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i] && s[i] != c)
			count++;
		if (s[i] == '\'' || s[i] == '\"')
			i += substr_len(&s[i]);
		while (s[i] && s[i] != c)
			i++;
	}
	return (count);
}

char	**ft_split_args(char const *s, char c)
{
	int		i;
	int		count;
	char	**arr;

	if (!s)
		return (NULL);
	arr = (char **)malloc(sizeof(char *) * (args_count(s, c) + 1));
	if (!arr)
		return (NULL);
	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i])
		{
			arr[count] = get_substr(&s[i], c);
			if (arr[count] == NULL)
				return (free_arr(arr, count));
			count++;
		}
		i += arg_len(s, c);
	}
	arr[count] = NULL;
	return (arr);
}

#include <stdio.h>

int main(void)
{
    char **result;
    int i;

    // Exemplo 1
    result = ft_split_args("one two 'three four' \"five six\"", ' ');
    for (i = 0; result[i]; i++)
        printf("Token: %s\n", result[i]);

    // Exemplo 2
    result = ft_split_args("  'hello world'  test \"another test\"  ", ' ');
    for (i = 0; result[i]; i++)
        printf("Token: %s\n", result[i]);

    return 0;
}
