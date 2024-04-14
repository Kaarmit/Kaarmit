/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 20:48:25 by aarmitan          #+#    #+#             */
/*   Updated: 2024/04/03 21:08:30 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int	ft_strlen(char *str)
{
	int	i = 0;

	while(str[i])
		i++;
	return (i);
}

char	*ft_strdup(char *src)
{
	int	i = 0;
	char	*dup;
	int	length;

	length = ft_strlen(src);
	dup = malloc(sizeof (char) * (length + 1));
	if (dup == NULL)
		return (NULL);
	while (src[i])
	{
		dup[i] = src[i];
		i++;
	}
	dup[i] = '\0'
	return (dup);
}
