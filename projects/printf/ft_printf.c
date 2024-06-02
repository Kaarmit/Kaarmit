/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 14:02:59 by aarmitan          #+#    #+#             */
/*   Updated: 2024/06/02 15:22:44 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_type(const char *str, )
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '%')
		{
			i++;
			if (str[i] == 'c')
			
			else if (str[i] == 's')

			else if (str[i] == 'p')

			else if (str[i] == 'd' || str[i] == 'i')

			else if (str[i] == 'u')

			else if (str[i] == 'x'|| str[i] == 'X')

		}
	}
}

int	ft_printf(const char *str, ...)
{
	va_list	args;
	int	output;

	va_start(args, str);
	output = 0;


	va_end(args);
	return (output);
}
