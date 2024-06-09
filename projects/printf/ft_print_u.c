/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_u.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 12:06:09 by aarmitan          #+#    #+#             */
/*   Updated: 2024/06/09 14:24:20 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_print_u(unsigned int value, int *output)
{
	if (value >= 10)
		ft_print_u(value / 10, output);
	ft_putchar_fd(value % 10 + '0', 1);
	(*output)++;
}
