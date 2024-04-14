/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atoiexam.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 13:44:37 by aarmitan          #+#    #+#             */
/*   Updated: 2024/03/29 14:01:28 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int	ft_atoi(char *str)
{
	int	i;
	int	sign;
	int	nb;

	nb = 0;
	sign = 1;
	i = 0;
	while (((str[i] >= 9) && (str[i] <= 13)) || (str[i] == 32))
	{
		i++;
	}
	if (str[i] == '-')
	{
		sign = (sign * -1);
		i++;
	}
	if (str[i] == '+')
		i++;
	while ((str[i] >= '0') && (str[i] <= '9'))
	{
		nb = nb * 10 + (str[i] - '0');
		i++;
	}
	return (nb * sign);
}

int	main(void)
{
	printf("%d\n", ft_atoi("   -123456"));
	return (0);
}

