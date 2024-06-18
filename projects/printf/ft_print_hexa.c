/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hexa.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 16:06:54 by aarmitan          #+#    #+#             */
/*   Updated: 2024/06/13 13:08:05 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t	ft_hexlen(unsigned int value)
{
	size_t	len;

	len = 0;
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
			ft_printchar(n + '0');
		else
		{
			if (c == 'x')
				ft_printchar(n - 10 + 'a');
			if (c == 'X')
				ft_printchar(n - 10 + 'A');
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
