/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strupcase.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 17:09:20 by aarmitan          #+#    #+#             */
/*   Updated: 2024/03/23 09:08:27 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <unistd.h>

char	*ft_strupcase(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if ((str[i] >= 'a') && (str[i] <= 'z'))
			str[i] = str[i] -32;
		i++;
	}
	return (str);
}
/*
int	main(void)
{
	char	str[] = "abcdefghijklmnopqrstuvwxyz";

	ft_strupcase(str);
	write(1, str, 26);
}
*/
