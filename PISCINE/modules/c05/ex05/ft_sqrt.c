/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sqrt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 15:49:31 by aarmitan          #+#    #+#             */
/*   Updated: 2024/03/31 18:24:51 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_sqrt(int nb)
{
	int	count;

	count = 1;
	while (count < nb / count)
		count ++;
	if (count * count == nb)
		return (count);
	else
		return (0);
}
/*
#include <stdio.h>

int	main(void)
{
	printf("10:%d\n", ft_sqrt(100));
	printf("6:%d\n", ft_sqrt(36));
	printf("0:%d\n", ft_sqrt(37));
	printf("100:%d\n", ft_sqrt(10000));
	printf("0:%d\n", ft_sqrt(10001));
	printf("2000:%d\n", ft_sqrt(4000000));
	printf("0:%d\n", ft_sqrt(-36));
}
*/
