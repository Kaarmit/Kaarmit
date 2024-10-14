/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 13:15:11 by ilymegy           #+#    #+#             */
/*   Updated: 2024/09/12 12:53:17 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

void	ft_bzero(void *s, size_t size)
{
	size_t	i;
	char	*data;

	i = 0;
	data = (char *)s;
	while (i < size)
	{
		data[i] = 0;
		i++;
	}
}
