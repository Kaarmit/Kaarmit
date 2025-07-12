/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abastian <abastian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 10:55:48 by abastian          #+#    #+#             */
/*   Updated: 2024/05/31 12:03:23 by abastian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_int_len(int n)
{
	int	count;

	if (n == 0)
		return (1);
	count = 0;
	if (n < 0)
	{
		count++;
		n *= -1;
	}
	while (n > 0)
	{
		n /= 10;
		count++;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	int		count;
	char	*res;
	int		negative;

	negative = 0;
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	count = ft_int_len(n);
	res = malloc(sizeof(char) * (count + 1));
	if (!res)
		return (NULL);
	if (n < 0)
	{
		negative = 1;
		n *= -1;
	}
	res[count] = '\0';
	while (count--)
	{
		res[count] = n % 10 + '0';
		n /= 10;
	}
	if (negative != 0)
		res[0] = '-';
	return (res);
}
