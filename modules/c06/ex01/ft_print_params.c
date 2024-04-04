/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_params.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 09:46:11 by aarmitan          #+#    #+#             */
/*   Updated: 2024/03/31 10:33:29 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_putstr(char *argv)
{
	int	i;

	i = 0;
	while (argv[i] != '\0')
	{
		write(1, &argv[i], 1);
		i++;
	}
}

int	main(int argc, char **argv)
{
	int	j;

	j = 1;
	while (argc > 1)
	{
		ft_putstr(argv[j]);
		write (1, "\n", 1);
		j++;
		argc--;
	}
	return (0);
}
