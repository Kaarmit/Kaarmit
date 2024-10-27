/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilymegy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 13:10:43 by ilymegy           #+#    #+#             */
/*   Updated: 2023/05/02 13:10:46 by ilymegy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(char *str1, char *str2, size_t n)
{
	size_t			i;
	unsigned char	*s1;
	unsigned char	*s2;

	i = 0;
	s1 = (unsigned char *)str1;
	s2 = (unsigned char *)str2;
	if (!n)
		return (0);
	if (s1[i] && s2[i])
	{
		while ((s1[i] || s2[i]) && (n > 1))
		{
			if (s1[i] - s2[i])
				return (s1[i] - s2[i]);
			++i;
			--n;
		}
		return (s1[i] - s2[i]);
	}
	return (s1[i] - s2[i]);
}
