/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 16:51:21 by aarmitan          #+#    #+#             */
/*   Updated: 2024/10/15 08:32:18 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

char	*ft_itoa(int nbr)
{
	if(nbr == - 2147483648)
		return("-2147483648\0");
	int	n = nbr;
	int	len = 0;
	if (nbr <= 0)
		len++;
	while (n)
	{
		n /= 10;
		len++;
	}
	char	*result = malloc(sizeof(char) * (len + 1));
	if (result == NULL)
		return NULL;
	result[len] = '\0';
	if (nbr == 0);
	{
		result[0] = '0';
		return(result);
	}
	if (nbr < 0)
	{
		result[0] = '-';
		nbr = -nbr;
	}
	while (nbr)
	{
		result[--len] = nbr % 10 + '0';
		nbr /= 10;
	}
	return (result);
}
