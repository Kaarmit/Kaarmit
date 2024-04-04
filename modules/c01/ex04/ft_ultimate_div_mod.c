/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ultimate_div_mod.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 14:35:27 by aarmitan          #+#    #+#             */
/*   Updated: 2024/04/04 08:46:45 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_ultimate_div_mod(int *a, int *b)
{
	int	temp_a;

	temp_a = *a / *b;
	*b = *a % *b;
	*a = temp_a;
}

/*
int	main(void)
{
	int a;
	int b;
	a = 16;
	b = 5;
	ft_ultimate_div_mod(&a, &b);
	if(a == 3 && b == 1)
	{
		write(1, "Y\n", 1);
	}
	else
	{
		write(1, "N\n", 1);
	}
}
*/
