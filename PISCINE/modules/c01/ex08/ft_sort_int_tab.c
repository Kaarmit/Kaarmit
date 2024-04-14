/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_int_tab.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 11:17:57 by aarmitan          #+#    #+#             */
/*   Updated: 2024/04/04 08:47:45 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	ft_sort_int_tab(int *tab, int size)
{
	int	i;
	int	temp;

	i = 0;
	while (i < size - 1)
	{
		if (tab[i] > tab[i + 1])
		{
			temp = tab[i];
			tab[i] = tab[i + 1];
			tab[i + 1] = temp;
		}
		i++;
	}
	if (size > 1)
		ft_sort_int_tab(tab, size - 1);
}
/*
#include <stdio.h>
int	main(void)
{
	int	tab[5] = {-10, 54, 42, 666, 3};

	ft_sort_int_tab(tab, 5);
	printf("ordre croissant :");
	printf("%d,%d,%d,%d,%d", tab[0], tab[1], tab[2], tab[3], tab[4]);
}
*/
