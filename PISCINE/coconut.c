/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coconut.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 15:00:00 by aarmitan          #+#    #+#             */
/*   Updated: 2024/04/03 15:26:57 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

int	main(int argc, char **argv)
{
	int	i = 0;

	while (argc == 2)
	{
		while (argv[1][i] != '\0')
		{
			write(1, &argv[1][i], 1);
			if (argv[1][i + 1] != '\0')
			{
				ft_putchar('_');
				ft_putchar('_');
				ft_putchar('_');
			}
			i++;
		}
		argv[1][i] = '\0';
		write (1, "\n", 1);
		return (0);
	}
	write(1, "\n", 1);	
	return (0);
}
