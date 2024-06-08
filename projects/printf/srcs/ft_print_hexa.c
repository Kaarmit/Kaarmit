/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hexa.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 16:06:54 by aarmitan          #+#    #+#             */
/*   Updated: 2024/06/08 14:54:44 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

size_t	ft_hexlen(unsigned int value)
{
	size_t	len;

	len = 0;
	if (value <= 0)
		len ++;
	while (value)
	{
		len++;
		value /= 16;
	}
	return (len);
}

void	ft_puthex(unsigned int n, const char c)
{
	if (n >= 16)
	{
		ft_puthex(n / 16, c);
		ft_puthex(n % 16, c);
	}
	else
	{
		if (n <= 9)
			ft_putchar_fd((n + '0'), 1);
		else
		{
			if (c == 'x')
				ft_putchar_fd((n - 10 + 'a'), 1);
			if (c == 'X')
				ft_putchar_fd((n - 10 + 'A'), 1);
		}
	}
}

void	ft_print_hexa(unsigned int value, const char c, int *output)
{
	if (value == 0)
		(*output) += (write(1, "0", 1));
	else
	{
		ft_puthex(value, c);
		(*output) += ft_hexlen(value);
	}
}
