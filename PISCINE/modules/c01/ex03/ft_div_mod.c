/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_div_mod.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 10:06:19 by aarmitan          #+#    #+#             */
/*   Updated: 2024/03/18 14:34:11 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_div_mod(int a, int b, int *div, int *mod)
{
	*div = a / b;
	*mod = a % b;
}

/*
int	main(void)
{
	int a;
	int b;
	int mod;
	int div;
	a = 16;
	b = 5;
	ft_div_mod(a, b, &div, &mod);
	if(div == 3 && mod == 1)
	{
		write(1, "Yes\n", 3);
	}
	else
	{
		write(1, "No\n", 2);
	}
}
*/
