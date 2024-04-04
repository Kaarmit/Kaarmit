/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotone.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 19:20:04 by aarmitan          #+#    #+#             */
/*   Updated: 2024/04/03 20:36:55 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int	ft_strlen(char *str)
{
	int	i = 0;

	while(str[i])
		i++;
	return (i);
}

void	rotone(char *str)
{
	int	i = 0;

	while (str[i])
	{
		if (((str[i] >= 'a') && (str[i] <= 'y')) || ((str[i] >= 'A') && (str[i] <= 'Y')))
			str[i] = str[i] + 1;
		else if ((str[i] == 'z') || (str[i] == 'Z'))
			str[i] = str[i] - 25;
		i++;
	}
}

int	main(int argc, char **argv)
{
	if (argc == 2)
	{
		rotone(argv[1]);
		write(1, argv[1], ft_strlen(argv[1]));
		write(1, "\n", 1);
	}
	return (0);
}
