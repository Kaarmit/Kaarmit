/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 13:00:06 by ilymegy           #+#    #+#             */
/*   Updated: 2024/09/12 12:55:23 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

void	*ft_memmove(void *dst, const void *src, size_t size)
{
	char	*data_dst;
	char	*data_src;

	if (!src && !dst)
		return (NULL);
	if (src > dst)
		dst = ft_memcpy(dst, src, size);
	else
	{
		data_dst = (char *)dst;
		data_src = (char *)src;
		while (size--)
			data_dst[size] = data_src[size];
	}
	return (dst);
}
