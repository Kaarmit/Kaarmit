/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilymegy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 14:22:11 by ilymegy           #+#    #+#             */
/*   Updated: 2023/05/03 14:22:27 by ilymegy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	len_res(long int n)
{
	int	len;

	len = 0;
	if (n <= 0)
		len++;
	while (n)
	{
		n /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int nb)
{
	long int	n;
	int			len;
	char		*res;

	n = (long int)nb;
	len = len_res(n);
	res = ft_calloc((len + 1), sizeof(char));
	if (!res)
		return (NULL);
	if (n == 0)
		res[0] = '0';
	if (n < 0)
	{
		res[0] = '-';
		n = -n;
	}
	len--;
	while (n)
	{
		res[len--] = (n % 10) + '0';
		n /= 10;
	}
	return (res);
}
