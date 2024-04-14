/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rot13.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 16:10:17 by aarmitan          #+#    #+#             */
/*   Updated: 2024/04/04 16:18:30 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int	ft_strlen(char*str)
{
	int	i = 0;

	while (str[i])
		i++;
	return (i);
}

void	rot13(char *str)
{
	int	i = 0;

	while (str[i])
	{
		if (((str[i] >= 'a') && (str[i] <= 'm')) || ((str[i] >= 'A') && (str[i] <= 'M')))
		{
			str[i] = str[i] + 13;
			i++;
		}
		else if (((str[i] >= 'n') && (str[i] <= 'z')) || ((str[i] >= 'N') && (str[i] <= 'Z')))
		{
			str[i] = str[i] - 13;
			i++;
                }
		else
			i++;
	}
}

int	main(int argc, char **argv)
{
	if (argc == 2)
	{
		rot13(argv[1]);
		write(1, argv[1], ft_strlen(argv[1]));
	}
	write(1, "\n", 1);
	return 0;
}
