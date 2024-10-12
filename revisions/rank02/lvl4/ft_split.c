/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 17:18:13 by aarmitan          #+#    #+#             */
/*   Updated: 2024/10/09 17:28:26 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>

char	*ft_strncpy(char *s1, char *s2, int n)
{
	int	i = -1;

	while (++i < n && s2[i])
		s1[i] = s2[i];
	s1[i] = '\0';
	return (s1);
}

char	**ft_split(char *str)
{
	int	i = 0;
	int	j = 0;
	int	k = 0;
	int	wc = 0;

	while (str[i])
	{
		while (str[i] && str[i] == ' ' || str[i] == '\t' || str[i] == '\n')
			i++;
		if (str[i])
			wc++;
		while (str[i] && (str[i] != ' ' && str[i] != '\t' && str[i] != '\n'))\
			i++;
	}

	char	**out = (char **)malloc(sizeof (char *) * (wc + 1));
	i = 0;

	while(str[i])
	{
		while (str[i] && (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'))
			i++;
		while (str[i] && (str[i] != ' ' && str[i] != '\t' && str[i] != '\n'))
			i++;
		if (i > j)
		{
			out[k] = (char *)malloc(sizeof(char) * ((i -j) + 1));
			ft_strncpy(out[k++], &str[j], i - j);
		}
	}
	out[k] = NULL;
	return (out);
}
