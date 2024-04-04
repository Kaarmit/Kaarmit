/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 08:18:50 by aarmitan          #+#    #+#             */
/*   Updated: 2024/03/19 08:54:20 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putnbr(int nb)
{
	if (nb == -2147483648) 
	{
        	ft_putchar('-');
        	ft_putchar('2');
        	ft_putnbr(147483648);
        	return;
	}
	if (nb < 0)
	{
		ft_putchar('-');
		 nb = -nb;
	}
	if (nb >= 10)
	{
		ft_putnbr(nb / 10);
	}
   	 ft_putchar(nb % 10 + '0');
}

int	main(void)
{
	ft_putnbr(42);
	return 0;
}




















