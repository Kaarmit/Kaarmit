/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_is_lowercase.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 14:35:53 by aarmitan          #+#    #+#             */
/*   Updated: 2024/03/23 08:55:39 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_str_is_lowercase(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if ((str[i] < 'a') || (str[i] > 'z'))
			return (0);
		i++;
	}
	return (1);
}

/*
#include <unistd.h>
int	main(void)
{
	char	*str = "abcdefghijklmnopqrstuvwxyz";

	int	p;

	p = ft_str_is_lowercase(str);
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
