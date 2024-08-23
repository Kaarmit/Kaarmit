/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 15:46:26 by aarmitan          #+#    #+#             */
/*   Updated: 2024/08/23 15:42:44 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*s1;
	unsigned char	*s2;

	s1 = (unsigned char *)dest;
	s2 = (unsigned char *)src;
	if (dest == NULL && src == NULL)
		return (NULL);
	if (s1 <= s2 || s1 >= (s2 + n))
		while (n--)
			*s1++ = *s2++;
	else
	{
		s1 += n - 1;
		s2 += n - 1;
		while (n--)
			*s1-- = *s2--;
	}
	return (dest);
}
