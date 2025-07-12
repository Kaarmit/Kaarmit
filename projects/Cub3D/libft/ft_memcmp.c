/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abastian <abastian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 17:07:47 by abastian          #+#    #+#             */
/*   Updated: 2024/05/27 17:24:12 by abastian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*p;
	unsigned char	*w;
	size_t			i;

	p = (unsigned char *)s1;
	w = (unsigned char *)s2;
	i = 0;
	while (i < n)
	{
		if (w[i] != p[i])
			return (p[i] - w[i]);
		i++;
	}
	return (0);
}
