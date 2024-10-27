/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilymegy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 12:58:31 by ilymegy           #+#    #+#             */
/*   Updated: 2023/05/02 12:58:39 by ilymegy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/*
** DESCRIPTION : La fonction memchr() examine les n premiers octets de la zone
** mémoire pointée par s à la recherche du caractère c. Le premier octet
** correspondant à c (interprété comme un unsigned char) arrête l'opération.
**
** VALEUR RENVOYEE : La fonction memchr() renvoit un pointeur sur l'octet
** correspondant, ou NULL si le caractère n'est pas présent dans la zone de
** mémoire concernée.
*/

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t size)
{
	size_t			i;
	unsigned char	*str;

	i = 0;
	str = (unsigned char *)s;
	while (i < size)
	{
		if (str[i] == (unsigned char)c)
			return (str + i);
		i++;
	}
	return (NULL);
}
