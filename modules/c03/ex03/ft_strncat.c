/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 20:13:33 by aarmitan          #+#    #+#             */
/*   Updated: 2024/03/26 15:12:59 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strncat(char *dest, char *src, unsigned int nb)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	j = 0;
	while (dest[j] != '\0')
	{
		j++;
	}
	while (src[i] != '\0' && i < nb)
	{
		dest[j + i] = src[i];
		i++;
	}
	dest[j + i] = '\0';
	return (dest);
}
/*
#include <unistd.h>
#include <stdio.h>
int	main(void)
{
	char	src[] = "ca va ? oui";
	char	dest[] = "salut ";
	unsigned int	nb = 7;

	printf("%s", ft_strncat(dest, src, nb));
	return (0);
}
*/
