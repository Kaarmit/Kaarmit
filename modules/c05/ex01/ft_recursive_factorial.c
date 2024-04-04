/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_recursive_factorial.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 13:39:56 by aarmitan          #+#    #+#             */
/*   Updated: 2024/03/31 18:55:25 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_recursive_factorial(int nb)
{
	if (nb < 0)
		return (0);
	if (nb == 0 || nb == 1)
		return (1);
	else
		return (nb *= ft_recursive_factorial(nb - 1));
}
/*
#include <stdio.h>

int	main(void)
{
	printf("0:%d\n", ft_recursive_factorial(-10));
	printf("0:%d\n", ft_recursive_factorial(-1));
	printf("1:%d\n", ft_recursive_factorial(0));
	printf("1:%d\n", ft_recursive_factorial(1));
	printf("3628800:%d\n", ft_recursive_factorial(10));
	printf("6:%d\n", ft_recursive_factorial(3));
}
*/
