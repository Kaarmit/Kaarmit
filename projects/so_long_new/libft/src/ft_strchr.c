/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 13:00:36 by ilymegy           #+#    #+#             */
/*   Updated: 2024/09/12 12:56:13 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

char	*ft_strchr(const char *string, int searchedChar)
{
	int	i;

	i = 0;
	if (!searchedChar)
		return ((char *)(string + ft_strlen(string)));
	while (string[i])
	{
		if (string[i] == ((unsigned char)searchedChar))
			return ((char *)(string + i));
		i++;
	}
	return (0);
}
