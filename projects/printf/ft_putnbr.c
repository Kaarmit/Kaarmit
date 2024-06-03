/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 13:46:43 by aarmitan          #+#    #+#             */
/*   Updated: 2024/06/03 17:15:17 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "ft_printf.h"

// int	get_len()
// {
// 	int	len;

// 	len = 1;
// 	if (n < 0)
// 		len++;
// 	while (n / 10 != 0)
// 	{
// 		len++;
// 		n /= 10;
// 	}
// 	return (len);
// }

int	ft_putnbr(int nb, int *printed)
{
	int	len;

	if (n == -2147483648)
	{
		write(1, "-2147483648", 11);
		return ;
	}
	if (n < 0)
	{
		ft_putchar('-');
		n = -n;
	}
	if (n > 9)
		ft_putnbr(n / 10);
	ft_putchar((n % 10) + '0');
	len = get_len();
	return (len);
}
