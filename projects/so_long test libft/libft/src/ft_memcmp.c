/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilymegy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 12:59:13 by ilymegy           #+#    #+#             */
/*   Updated: 2023/05/02 12:59:35 by ilymegy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/*
** DESCRIPTION : La fonction memcmp() compare les n premiers octets des zones
** mémoire s1 et s2. Elle renvoie un entier inférieur, égal, ou supérieur à
** zéro, si s1 est respectivement inférieure, égale ou supérieur à s2.
**
** VALEUR RENVOYEE : La fonction memcmp() renvoie un entier négatif, nul ou
** positif si les n premiers octets de s1 sont respectivement inférieurs,
** égaux ou supérieurs aux n premiers octets de s2.
*/

#include "libft.h"

int	ft_memcmp(const void *p1, const void *p2, size_t size)
{
	char	*s1;
	char	*s2;
	size_t	i;

	if (size == 0)
		return (0);
	i = 0;
	s1 = (char *)p1;
	s2 = (char *)p2;
	while (size--)
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}
