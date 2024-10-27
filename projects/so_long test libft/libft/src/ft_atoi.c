/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilymegy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 13:18:12 by ilymegy           #+#    #+#             */
/*   Updated: 2023/05/02 13:18:17 by ilymegy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/*
** Transforme une chaine de caracteres en entier.
** Convert a string to integer.
*/

#include "libft.h"

int	ft_atoi(const char *str)
{
	int			minus;
	long int	res;

	minus = 1;
	res = 0;
	while (*str == 32 || (*str >= '\t' && *str <= '\r'))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			minus = -minus;
		str++;
	}
	while (*str >= 48 && *str <= 57)
		res = res * 10 + *str++ - 48;
	return (res * minus);
}
