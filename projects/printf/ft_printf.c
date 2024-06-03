/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 14:02:59 by aarmitan          #+#    #+#             */
/*   Updated: 2024/06/03 17:16:17 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putchar(char c, int *output)
{
	write(1, &c, 1);
	(*output)++;
}

int	ft_putstr(char *str, int *output)
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
		ft_putchar(str[i], output);
		i++;
	}
	return (i)
}
void	print_type(const char c, va_list value, int *output)
{
	if (c == 'c')
	{
		++(*output);
		ft_putchar(va_arg(value, int), output);
	}
	else if (c == 's')
		ft_putstr(va_arg(value, char *), output);
	else if (c == 'p')
		ft_put_pointer(va_arg(value, unsigned long long), output);
	else if (c == 'd' || c == 'i')
		ft_putnbr(va_arg(value, int), output);
	else if (c == 'u')
		ft_putnbr_unsigned(va_arg(value, unsigned int), output);
	else if (c == 'x'|| c == 'X')
		ft_put_hex(va_arg(value, unsigned int), output);
	else if (c != 0)
		ft_putchar(c);
}

int	ft_printf(const char *str, ...)
{
	va_list	args;
	int	output;
	int	i;

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
				ft_putchar('%', &output);
			else
				print_type(str[i], args, &output);
		}
		i++;
		output++;
	}
	va_end(args);
	return (output);
}
