/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilymegy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 13:00:19 by ilymegy           #+#    #+#             */
/*   Updated: 2023/05/02 13:00:22 by ilymegy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/*
** DESCRIPTION : La fonction memset() remplit les n premiers octets de la zone
** mémoire pointée par b avec l'octet c.
**
** VALEUR RENVOYEE : La fonction memset() renvoie un pointeur sur la zone
** mémoire b.
*/

#include "libft.h"

void	*ft_memset(void *pointer, int value, size_t count)
{
	size_t	i;
	char	*buffer;

	i = 0;
	buffer = (char *)pointer;
	while (i < count)
	{
		buffer[i] = value;
		i++;
	}
	return (pointer);
}
