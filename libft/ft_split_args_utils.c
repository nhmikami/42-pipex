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

#include "libft.h"

static int	substr_len(char const *str)
{
	int	len;

	len = 0;
	if (str[len] == '\'')
	{
		len++;
		while (str[len] && str[len] != '\'')
			len++;
		if (str[len] == '\'')
			len++;
	}
	else if (str[len] == '\"')
	{
		len++;
		while (str[len] && str[len] != '\"')
			len++;
		if (str[len] == '\"')
			len++;
	}
	return (len);
}

int	arg_len(char const *str, char c)
{
	int	len;

	len = 0;
	while (str[len] && str[len] != c)
	{
		if (str[len] == '\'' || str[len] == '\"')
			len += substr_len(&str[len]);
		else
			len++;
	}
	return (len);
}

static char	*allocate_substr(char const *s, char c, int *len)
{
	char	*str;

	if (*s == '\'' || *s == '\"')
		*len = arg_len(s, c) - 2;
	else
		*len = arg_len(s, c);
	str = malloc(sizeof(char) * (*len + 1));
	if (!str)
		return (NULL);
	return (str);
}

char	*get_substr(char const *s, char c)
{
	int		i;
	int		len;
	char	*str;
	char	quote;

	str = allocate_substr(s, c, &len);
	if (!str)
		return (NULL);
	i = 0;
	while (i < len)
	{
		if (*s == '\'' || *s == '\"')
		{
			quote = *s++;
			while (*s && *s != quote)
				str[i++] = *s++;
			if (*s == quote)
				s++;
		}
		else
			str[i++] = *s++;
	}
	str[i] = '\0';
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
