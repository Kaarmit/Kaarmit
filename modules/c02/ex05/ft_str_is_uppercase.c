/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_is_uppercase.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 14:45:34 by aarmitan          #+#    #+#             */
/*   Updated: 2024/03/23 08:57:09 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_str_is_uppercase(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if ((str[i] < 'A') || (str[i] > 'Z'))
		{
			return (0);
		}
		i++;
	}
	return (1);
}

/*
#include <unistd.h>
int	main(void)
{
	char	*str = "ABCDEdFGHIJKLMNOPQRSTUVWXYZ";

	int	p;
	p = ft_str_is_uppercase(str);
	if (p == 1)
	{
		write(1, "yes", 3);
	}
	else
	{
		write(1,"no", 2);
	}
}
*/	
