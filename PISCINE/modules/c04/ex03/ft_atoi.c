/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 09:30:46 by aarmitan          #+#    #+#             */
/*   Updated: 2024/03/27 17:47:52 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_atoi(char *str)
{
	int	i;
	int	nb;
	int	sign;

	sign = 1;
	i = 0;
	nb = 0;
	while (((str[i] >= 9) && (str[i] <= 13)) || (str[i] == 32))
		i++;
	while ((str[i] == '+') || (str[i] == '-'))
	{
		if (str[i] == '-')
		{
			sign = (sign * (-1));
		}
		i++;
	}
	while ((str[i] >= '0') && (str[i] <= '9'))
	{
		nb = nb * 10 + (str[i] - '0');
		i++;
	}
	return (nb * sign);
}
/*
#include <stdio.h>
int	main(int ac, char **av)
{
	if (ac == 2)
		printf("soluce:%d", ft_atoi(av[1]));
	return (0);
}*/
