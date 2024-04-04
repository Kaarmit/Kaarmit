/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rrange.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 16:54:20 by aarmitan          #+#    #+#             */
/*   Updated: 2024/04/04 17:39:24 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int	*ft_rrange(int start, int end)
{
	int	i = 0;
	int	*tab;
	int	size;

	size = end - start;
	if (start >= end)
		return (NULL);
	tab = malloc(sizeof (int) * size);
	if (tab == NULL)
		return (NULL);
	while (end != start)
	{
		tab[i] = end;
		end--;
		i++;
	}
	return (tab);	
}
#include <stdio.h>

int    main(void)
{
	int *range;

	range = ft_rrange(0, 5);
	printf("5, 4, 3, 2, 1, 0 : %d, %d, %d, %d, %d, %d\n",
			range[0], range[1], range[2], range[3], range[4], range[5]);

	range = ft_rrange(-10, 10);
	printf("10, -9 : %d, %d", range[0], range[19]);
}
