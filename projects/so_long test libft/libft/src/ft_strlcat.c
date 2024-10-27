/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilymegy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 13:01:04 by ilymegy           #+#    #+#             */
/*   Updated: 2023/05/02 13:01:08 by ilymegy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	len_d;
	size_t	len_s;

	len_s = ft_strlen(src);
	len_d = ft_strlen(dst);
	i = 0;
	if (len_d < size - 1 && size > 0)
	{
		while (src[i] && len_d + i < size - 1)
		{
			dst[len_d + i] = src[i];
			i++;
		}
		dst[len_d + i] = 0;
	}
	if (len_d >= size)
		len_d = size;
	return (len_d + len_s);
}

// https://github.com/0x050f/libft-war-machine
