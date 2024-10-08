/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 13:10:58 by ilymegy           #+#    #+#             */
/*   Updated: 2024/09/12 12:57:09 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

char	*ft_strnstr(const char *big, const char *lil, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	lil_len;

	if (!lil[0])
		return ((char *)big);
	i = 0;
	lil_len = ft_strlen(lil);
	while (big[i] && (i + lil_len - 1) < len)
	{
		j = 0;
		while (lil[j] && big[i + j] == lil[j])
		{
			if (j == lil_len - 1)
				return ((char *)(big + i));
			j++;
		}
		i++;
	}
	return (0);
}
