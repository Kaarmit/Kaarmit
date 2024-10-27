/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilymegy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 13:11:08 by ilymegy           #+#    #+#             */
/*   Updated: 2023/05/02 13:11:10 by ilymegy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
