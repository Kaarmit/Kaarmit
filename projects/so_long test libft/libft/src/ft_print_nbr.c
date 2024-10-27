/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_nbr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilymegy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 15:56:03 by ilymegy           #+#    #+#             */
/*   Updated: 2023/05/16 15:56:08 by ilymegy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

int	int_len(long int num)
{
	int	len;

	len = 0;
	if (num == 0)
		return (1);
	if (num < 0)
		len++;
	while (num != 0)
	{
		len++;
		num = num / 10;
	}
	return (len);
}

char	*p_nbr(int nbr)
{
	long int	n;
	int			len;
	char		*res;

	n = nbr;
	len = int_len(n);
	res = (char *)malloc(sizeof(char) * (len + 1));
	res[len] = '\0';
	if (n < 0)
	{
		res[0] = '-';
		n = -n;
	}
	else if (n == 0)
	{
		res[0] = 0 + 48;
	}
	while (n > 0)
	{
		res[--len] = n % 10 + 48;
		n = n / 10;
	}
	return (res);
}
