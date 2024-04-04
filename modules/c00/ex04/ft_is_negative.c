/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_negative.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 19:14:48 by aarmitan          #+#    #+#             */
/*   Updated: 2024/03/20 19:21:56 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_is_negative(int n)
{
	if(n < 0)
	{
		write(1, "N", 1);
	}
	else
	{	
		write(1, "P", 1);
	}
}

/*
int	main(void)
{
	ft_is_negative(1);
	ft_is_negative(0);
	ft_is_negative(-1);
}
*/
