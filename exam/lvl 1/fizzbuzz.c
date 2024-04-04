/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fizzbuzz.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 17:44:28 by aarmitan          #+#    #+#             */
/*   Updated: 2024/04/04 18:20:04 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putnbr(int nb)
{
	if (nb >=10)
		ft_putnbr(nb / 10);
	putchar(nb % 10 + '0');
}

void	fizzbuzz(int nb)
{

	while (nb != 100)
	{
		if ((nb % 3 == 0) && (nb % 5 == 0))
			write(1, "fizzbuzz", 8);
		else if (nb % 3 == 0)
			write(1, "fizz", 4);
		else if (nb % 5 == 0)
			write(1, "buzz", 4);
		else
			ft_putnbr(nb);
		write(1, "\n", 1);
		nb++;
	}	
}

int	main(void)
{
	fizzbuzz(1);
	return (0);
}
