/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 14:02:59 by aarmitan          #+#    #+#             */
/*   Updated: 2024/06/08 15:13:47 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int	ft_printchar(char c)
{
	write(1, &c, 1);
	return (1);
}

int	ft_printstr(char *str, int *output)
{
	int	i;

	i = 0;
	if (!str)
	{
		write(1, "(null)", 6);
		(*output) += 6;
		return (6);
	}
	while (str[i])
	{
		ft_printchar(str[i]);
		i++;
	}
	return (i);
}

void	print_type(const char c, va_list value, int *output)
{
	if (c == 'c')
	{
		++(*output);
		ft_printchar(va_arg(value, int));
	}
	else if (c == 's')
		ft_printstr(va_arg(value, char *), output);
	else if (c == 'p')
		ft_print_ptr(va_arg(value, unsigned long long), output);
	else if (c == 'd' || c == 'i')
		ft_print_id(va_arg(value, int), output);
	else if (c == 'u')
		ft_print_u(va_arg(value, unsigned int), output);
	else if (c == 'x' || c == 'X')
		ft_print_hexa(va_arg(value, unsigned int), c, output);
	else if (c != 0)
		ft_printchar(c);
}

int	ft_printf(const char *str, ...)
{
	va_list	args;
	int		output;
	int		i;

	va_start(args, str);
	output = 0;
	i = 0;
	if (!str)
		return (va_end(args), -1);
	while (str[i])
	{
		if (str[i] == '%')
		{
			i++;
			if (str[i] == '%')
				output += ft_printchar(str[0]);
			else
				print_type(str[i], args, &output);
		}
		i++;
		output++;
	}
	va_end(args);
	return (output);
}
