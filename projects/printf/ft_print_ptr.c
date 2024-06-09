/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_ptr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 16:07:24 by aarmitan          #+#    #+#             */
/*   Updated: 2024/06/09 15:32:37 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t	ft_ptrlen(uintptr_t n)
{
	size_t	len;

	len = 0;
	while (n)
	{
		n /= 16;
		len++;
	}
	return (len);
}

void	ft_putptr(uintptr_t n)
{
	if (n >= 16)
	{
		ft_putptr(n / 16);
		ft_putptr(n % 16);
	}
	else
	{
		if (n <= 9)
			ft_putchar_fd((n + '0'), 1);
		else
			ft_putchar_fd((n - 10 + 'a'), 1);
	}
}

void	ft_print_ptr(unsigned long long n, int *output)
{
	if (n == 0)
		(*output) += write(1, "(nil)", 5);
	else
	{
		(*output) += write(1, "0x", 2);
		ft_putptr(n);
		(*output) += ft_ptrlen(n);
	}
}
