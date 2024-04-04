/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_is_alpha.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 16:18:30 by aarmitan          #+#    #+#             */
/*   Updated: 2024/03/24 15:08:03 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_str_is_alpha(char *str)
{
	int	i;

	if (str[0] == '\0')
		return (1);
	i = 0;
	while (str[i] != '\0')
	{
		if ((str[i] < 'a' || str[i] > 'z')
			&& (str[i] < 'A' || str[i] > 'Z'))
			return (0);
		i++;
	}
	return (1);
}

/*
#include <unistd.h>
#include <stdio.h>

int	main(void)
{
	char	*str = "f56";
	
	int	p;

	p = ft_str_is_alpha(str);
	if (p == 1)
	{	
		write(1, "yes", 3);
	}
	else
	{
		write (1, "no", 2);
	}
}
*/
