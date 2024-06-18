/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_u.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 12:06:09 by aarmitan          #+#    #+#             */
/*   Updated: 2024/06/13 13:20:32 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_print_u(unsigned int n, int *output)
{
	if (n >= 10)
		ft_print_u(n / 10, output);
	ft_printchar(n % 10 + '0');
	(*output)++;
}
