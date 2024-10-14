/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 13:00:19 by ilymegy           #+#    #+#             */
/*   Updated: 2024/09/12 12:55:26 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

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
