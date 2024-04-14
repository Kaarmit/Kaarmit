/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ultimate_range.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 12:09:52 by aarmitan          #+#    #+#             */
/*   Updated: 2024/04/03 16:38:53 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int	ft_ultimate_range(int **range, int min, int max)
{
	int	*tab;
	int	size;
	int	i;

	size = max - min;
	i = 0;
	if (min >= max)
	{
		range = NULL;
		return (0);
	}
	tab = malloc(sizeof(int) * (size + 1));
	if (tab == NULL)
		return (-1);
	while (i < size)
	{
		tab[i] = min + i;
		i++;
	}
	*range = tab;
	return (size);
}
