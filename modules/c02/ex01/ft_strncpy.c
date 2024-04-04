/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 11:29:00 by aarmitan          #+#    #+#             */
/*   Updated: 2024/03/24 09:14:40 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <unistd.h>

char	*ft_strncpy(char *dest, char *src, unsigned int n)
{
	unsigned int	i;

	i = 0;
	while (i < n && src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	while (i < n)
	{
		dest[i] = '\0';
		i++;
	}	
	return (dest);
}

/*
#include <stdio.h>
int	main(void)
{
	char	*src = "Hello world";
	char	dest[12] = "";
	unsigned int	n = 7;

	printf("%s", ft_strncpy(dest, src, n));
	return(0);
}
*/
