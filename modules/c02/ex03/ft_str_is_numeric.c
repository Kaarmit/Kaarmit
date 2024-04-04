/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_is_numeric.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 13:49:57 by aarmitan          #+#    #+#             */
/*   Updated: 2024/03/23 21:32:05 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_str_is_numeric(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if ((str[i] < '0') || (str[i] > '9'))
			return (0);
		i++;
	}
	return (1);
}

/*
#include <unistd.h>
int	main(void)
{
	char	*str = "01f23456789";

	int	p;
	
	p = ft_str_is_numeric(str);
	if (p == 1)
	{
		write(1, "yes", 3);
	}
	else
	{
		write(1, "no", 2);
	}
}
*/
