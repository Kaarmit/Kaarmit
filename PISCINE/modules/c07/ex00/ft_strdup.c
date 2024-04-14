/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 08:48:58 by aarmitan          #+#    #+#             */
/*   Updated: 2024/04/03 14:44:42 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		i++;
	}
	return (i);
}

char	*ft_strdup(char *src)
{
	int		i;
	int		length;
	char	*s2;

	length = ft_strlen(src);
	i = 0;
	s2 = malloc((length + 1) * sizeof (char));
	if (s2 == NULL)
	{
		return (NULL);
	}
	while (src[i])
	{
		s2[i] = src[i];
		i++;
	}
	s2[i] = '\0';
	return (s2);
}
