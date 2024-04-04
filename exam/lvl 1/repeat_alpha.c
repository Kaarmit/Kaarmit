/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   repeat_alpha.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 12:51:31 by aarmitan          #+#    #+#             */
/*   Updated: 2024/04/04 15:25:07 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int	main(int argc, char **argv)
{
	int	repeat = 0;
	int	i = 0;

	if(argc == 2)
	{	
		while (argv[1][i] != '\0')
		{
			repeat = 0;
			if ((argv[1][i] >= 'a') && (argv[1][i] <= 'z'))
			{
				repeat += argv[1][i] - 'a' + 1;
				while (repeat)
				{
					write(1, &argv[1][i], 1);
					repeat--;
				}
			}
			else if ((argv [1][i] >= 'A') && (argv[1][i]))
			{
				repeat += argv[1][i] - 'A' + 1;
				while (repeat)
				{
					write(1, &argv[1][i], 1);
					repeat--;
				}

			}
			else
				write(1, &argv[1][i], 1);
			i++;
		}
	}
}

