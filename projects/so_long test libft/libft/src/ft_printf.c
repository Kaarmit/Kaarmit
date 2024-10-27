/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilymegy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 15:51:53 by ilymegy           #+#    #+#             */
/*   Updated: 2023/05/16 15:52:02 by ilymegy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"
#include <stdio.h>

int	err(const char *str)
{
	while (*str)
	{
		if (*str == '%' && (*(str + 1) != '%' && *(str - 1) != '%'))
		{
			if (search_str("csdiupxX", *(str + 1)) == -1)
				return (1);
		}
		str += 2;
	}
	return (0);
}

int	p_char(char c)
{
	return (write(1, &c, 1));
}

int	p_str(char *res, int *res_l)
{
	size_t	i;

	i = 0;
	if (res == NULL)
		*res_l += write(1, "(null)", 6);
	else if (res[0] == '\0')
		*res_l += 0;
	else
	{
		while (res[i])
		{
			*res_l += p_char(res[i]);
			i++;
		}
	}
	free(res);
	return (0);
}

int	print_it(const char *str, va_list p, int *res_l)
{
	while (*str)
	{
		if (*str == '%')
		{
			str++;
			if (*str == 'c')
				*res_l += p_char((unsigned char)va_arg(p, int));
			else if (*str == 's')
				p_str(ft_strdup(va_arg(p, char *)), res_l);
			else if (*str == 'd' || *str == 'i')
				p_str(p_nbr(va_arg(p, int)), res_l);
			else if (*str == 'u' || *str == 'x' || *str == 'X')
				p_str(p_uint(va_arg(p, unsigned int), *str), res_l);
			else if (*str == 'p')
				*res_l += p_ptr(va_arg(p, unsigned long long));
			else if (*str == '%')
				*res_l += write(1, "%", 1);
		}
		else
			*res_l += write(1, str, 1);
		str++;
	}
	return (0);
}

int	ft_printf(const char *str, ...)
{
	int		output_len;
	va_list	params;

	va_start(params, str);
	output_len = 0;
	if (str && *str && !err(str))
		print_it(str, params, &output_len);
	va_end(params);
	return (output_len);
}
