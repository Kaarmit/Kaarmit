/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_ptr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 16:07:24 by aarmitan          #+#    #+#             */
/*   Updated: 2024/06/08 14:54:54 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static size_t	ft_ptrlen(uintptr_t n)
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

static void	ft_putptr(uintptr_t n)
{
	if (n >= 16)
	{
		ft_puttptr(n / 16);
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
	(*output) += write(1, "0x", 2);
	if (n == 0)
		(*output) += write(1, "0", 1);
	else
	{
		ft_putptr(n);
		(*output) += ft_ptrlen(n);
	}
}
