/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aff_first_param.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 11:56:34 by aarmitan          #+#    #+#             */
/*   Updated: 2024/03/30 12:05:52 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int	ft_strlen(char *argv)
{
	int	i;

	i = 0;
	while (argv[i])
	{
		i++;
	}
	return (i);
}
	

int	main(int argc, char **argv)
{
	if (argc < 2)
	{
		write(1, "\n", 1);
	}
	write(1, argv[1], ft_strlen(argv[1]));
	write(1, "\n", 1);
}
