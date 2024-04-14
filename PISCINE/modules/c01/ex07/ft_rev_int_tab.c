/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rev_int_tab.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 08:21:21 by aarmitan          #+#    #+#             */
/*   Updated: 2024/04/04 08:47:29 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_rev_int_tab(int *tab, int size)
{
	int	start;
	int	temp;
	int	end;

	start = 0;
	end = size - 1;
	while (start <= end)
	{
		temp = tab[start];
		tab[start] = tab[end];
		tab[end] = temp;
		start++;
		end--;
	}
}
/*
#include <stdio.h>
int	main(void)
{
	int	tab[5] = {5, 4, 3, 2, 1};
	ft_rev_int_tab(tab, 5);
	printf("%d,%d,%d,%d,%d", tab[0], tab[1], tab[2], tab[3], tab[4]);
	return (0);
}
*/
