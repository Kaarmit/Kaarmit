/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_and_replace.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 10:47:46 by aarmitan          #+#    #+#             */
/*   Updated: 2024/04/02 12:58:40 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int	main(int argc, char **argv)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (argc == 4)
	{
		if (!argv[2][1] && !argv[3][1])
		{
			while (argv[1][i])
			{
				if (argv[1][i] == argv[2][j])
					write(1, &argv[3][j], 1);
				else
					write(1, &argv[1][i], 1);
				i++;
			}
		}
	}
	write(1, "\n", 1);
	return (0);	
}
