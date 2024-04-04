/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 14:09:04 by aarmitan          #+#    #+#             */
/*   Updated: 2024/04/03 16:36:42 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strcat(char *dest, char *src)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (dest[j])
		j++;
	while (src[i])
	{
		dest[j + i] = src[i];
		i++;
	}
	dest[j + i] = '\0';
	return (dest);
}

int	calculate_len(int size, char **strs, char *sep)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (i < size)
	{
		count = count + ft_strlen(strs[i]);
		i++;
	}
	count = count + (size - 1) * ft_strlen(sep) + 1;
	return (count);
}

char	*ft_strjoin(int size, char **strs, char *sep)
{
	char	*str;
	int		i;

	i = 0;
	if (size == 0)
	{
		str = malloc(sizeof(char));
		if (str == NULL)
			return (NULL);
		str[0] = '\0';
		return (str);
	}
	str = malloc(sizeof(char) * (calculate_len(size, strs, sep) + 1));
	if (str == NULL)
		return (NULL);
	str[0] = '\0';
	while (i < size)
	{
		ft_strcat(str, strs[i]);
		if (i != size - 1)
			ft_strcat(str, sep);
		i++;
	}
	return (str);
}
/*
#include <stdio.h>

int	main(int argc, char **argv)
{
	printf("output___said___this___is___a___success :\n");
	printf("%s\n",  ft_strjoin(argc, argv, "___"));
}
*/
