/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilymegy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 12:59:51 by ilymegy           #+#    #+#             */
/*   Updated: 2023/05/02 12:59:55 by ilymegy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/*
** DESCRIPTION : La fonction memcpy() copie n octets depuis la zone mémoire
** src vers la zone mémoire dst. Les deux zones ne doivent pas se chevaucher.
** Si c'est le cas, utilisez plutôt memmove(3).
**
** VALEUR RENVOYEE : La fonction memcpy() renvoie un pointeur sur dest.
*/

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t size)
{
	size_t	i;
	char	*dst_data;
	char	*src_data;

	if (!src || !dst)
		return (dst);
	i = 0;
	dst_data = (char *)dst;
	src_data = (char *)src;
	while (i < size)
	{
		dst_data[i] = src_data[i];
		i++;
	}
	return (dst);
}
