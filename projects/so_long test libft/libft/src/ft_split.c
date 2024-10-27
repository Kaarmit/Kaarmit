/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilymegy <ilyanamegy@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 19:55:25 by ilymegy           #+#    #+#             */
/*   Updated: 2023/08/17 22:01:20 by ilymegy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	words_count(const char *s, char sep)
{
	int	count;

	count = 0;
	while (*s)
	{
		while (*s == sep)
			++s;
		if (*s)
			++count;
		while (*s && *s != sep)
			++s;
	}
	return (count);
}

static int	give_to(char **tab, char const *s, char sep)
{
	char		**res;
	char const	*tmp;

	tmp = s;
	res = tab;
	while (*tmp)
	{
		while (*s == sep)
			++s;
		tmp = s;
		while (*tmp && *tmp != sep)
			++tmp;
		if (*tmp == sep || tmp > s)
		{
			*res = ft_substr(s, 0, tmp - s);
			if (!(*res))
				return (1);
			s = tmp;
			++res;
		}
	}
	*res = NULL;
	return (0);
}

char	**ft_split(char *s, char sep)
{
	char	**res;
	int		err;

	if (!s)
		return (NULL);
	err = 0;
	res = (char **)malloc((words_count(s, sep) + 1) * sizeof(char *));
	if (!res)
		return (NULL);
	err = give_to(res, s, sep);
	free(s);
	if (err)
		return (NULL);
	return (res);
}
