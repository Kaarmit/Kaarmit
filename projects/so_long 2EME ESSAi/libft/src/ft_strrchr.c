/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 13:11:08 by ilymegy           #+#    #+#             */
/*   Updated: 2024/09/12 12:57:12 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

char	*ft_strrchr(const char *string, int searchedChar)
{
	int		i;
	char	*res;

	i = 0;
	res = 0;
	while (string[i])
	{
		if (string[i] == ((unsigned char)searchedChar))
			res = (char *)(string + i);
		i++;
	}
	if (string[i] == ((unsigned char)searchedChar))
		res = (char *)(string + i);
	return (res);
}
