/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rev_params.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 18:21:24 by aarmitan          #+#    #+#             */
/*   Updated: 2024/03/31 10:32:16 by aarmitan         ###   ########.fr       */
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

	j = -1;
	while (argc + j >= 1)
	{
		ft_putstr(argv[argc + j]);
		write (1, "\n", 1);
		j--;
	}
}		
