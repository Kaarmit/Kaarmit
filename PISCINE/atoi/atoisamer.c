/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atoisamer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 17:05:15 by aarmitan          #+#    #+#             */
/*   Updated: 2024/04/03 17:12:03 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	atoi(char *str)
{
	int	i = 0;
	int	nb = 0;
	int	sign = 1;

	while (((str[i] >= 9) && (str[i] <= 13)) || (str[i] == 32))
		i++;
	if (str[i] == '+')
		i++;
	if (str[i] == '-')
	{
		sign = (sign * (-1));
		i++;
	}
	while ((str[i] >= '0') && (str[i] <= '9'))
	{
		nb = nb * 10 + (str[i] - '0');
		i++;
	}
	return (nb * sign);
}

#include <stdio.h>
int	main(void)
{
	printf("%d", atoi("  +134586aaa7"));
	return (0);
}
	
