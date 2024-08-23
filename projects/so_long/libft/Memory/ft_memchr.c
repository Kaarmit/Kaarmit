/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 13:15:07 by aarmitan          #+#    #+#             */
/*   Updated: 2024/08/23 15:42:28 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	while (n--)
	{
		if ((*(unsigned char *) s) == (unsigned char)c)
			return ((void *)s);
		s++;
	}
	return (NULL);
}
