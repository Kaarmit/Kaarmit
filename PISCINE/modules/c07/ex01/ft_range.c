/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_range.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 09:23:40 by aarmitan          #+#    #+#             */
/*   Updated: 2024/04/03 16:40:57 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int	*ft_range(int min, int max)
{
	int	*tab;
	int	i;
	int	size;

	i = 0;
	size = max - min;
	if (min >= max)
		return (NULL);
	tab = malloc(sizeof(int) * (size + 1));
	if (tab == NULL)
		return (NULL);
	while (i < size)
	{
		tab[i] = min + i;
		i++;
	}
	return (tab);
}
