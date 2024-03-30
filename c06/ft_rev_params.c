/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rev_params.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 11:57:10 by aarmitan          #+#    #+#             */
/*   Updated: 2024/03/29 12:06:52 by aarmitan         ###   ########.fr       */
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

	j = argc -1;
	while(argc > 1)
	{
		ft_putstr(argv[j]);
		write (1, "\n", 1);
		j--;
		argc--;
	}
	return (0);
}

