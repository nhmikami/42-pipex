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

char	**ft_split_args(char const *s, char c)
{
	int		count;
	char	**arr;

	if (!s)
		return (NULL);
	arr = (char **)malloc(sizeof(char *) * (args_count(s, c) + 1));
	if (!arr)
		return (NULL);
	count = 0;
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (*s)
		{
			arr[count] = get_substr(s, c);
			if (arr[count] == NULL)
				return (free_arr(arr, count));
			count++;
		}
		s += arg_len(s, c);
	}
	arr[count] = NULL;
	return (arr);
}
