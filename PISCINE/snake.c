/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   snake.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 08:37:46 by aarmitan          #+#    #+#             */
/*   Updated: 2024/03/29 10:32:56 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>

void        alpha_mirror(char *str)
{
	int	i;

	i = 0;
	while ((str[i] >= 97 && str[i] <= 122) && (str[i]))
	{
		str[i] = 219 - str[i];
		i++;
	}
	while (str[i] >= 65 && str[i] <= 90)
	{
		str[i] = 155 - str[i];
		i++;
	}
}

int	main(void)
{
	char	str[27] = "abcdefghijklmnopqrstuvwxyz";
	char	strb[27] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	alpha_mirror(str);
	alpha_mirror(strb);
	printf("%s\n", str);
	printf("%s\n", strb);
	return (0);
}

