/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlowcase.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 18:06:16 by aarmitan          #+#    #+#             */
/*   Updated: 2024/03/23 09:15:18 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strlowcase(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if ((str[i] >= 'A') && (str[i] <= 'Z'))
			str[i] = str[i] +32;
		i++;
	}
	return (str);
}
/*
#include <unistd.h>

int	main(void)
{
	char	str[] = "ABCDEFGHIJKLMNOPQRSTUVWXZ";
	
	ft_strlowcase(str);
	write(1, str, 26);
}
*/
