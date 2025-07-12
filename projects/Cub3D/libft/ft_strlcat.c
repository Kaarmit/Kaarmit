/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abastian <abastian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 12:07:22 by abastian          #+#    #+#             */
/*   Updated: 2024/05/24 18:19:38 by abastian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t siz)
{
	size_t	i;
	size_t	src_len;
	size_t	dest_len;

	src_len = 0;
	i = 0;
	dest_len = 0;
	while (src[src_len])
		src_len++;
	while (dst[dest_len] && dest_len < siz)
		dest_len++;
	if (siz == 0)
		return (src_len);
	i = dest_len;
	while (src[i - dest_len] && i < siz -1)
	{
		dst[i] = src[i - dest_len];
		i++;
	}
	if (dest_len < siz)
		dst[i] = '\0';
	return (dest_len + src_len);
}
