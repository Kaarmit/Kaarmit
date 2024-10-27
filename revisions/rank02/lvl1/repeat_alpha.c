/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   repeat_alpha.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 13:37:07 by aarmitan          #+#    #+#             */
/*   Updated: 2024/10/17 13:40:15 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int	main(int argc, char **argv)
{
	int	i;
	int	count;

	if(argc == 2)
	{
		i = 0;
		while (rgv[1][i])
		{
			if (argv[i][i] >= 'a' && argv[1][i] <= 'z')
				count = argv[1][i] - 'a' + 1;
			else if (argv[i][i] >= 'A' && argv[1][i] <= 'Z')
				count = argv[1][i] - 'A' + 1;
			else
				count = 1;
			while (count--)
				write(1, &argv[1][i], 1);
			i++;
		}
	}
	write(1, "\n", 1);
	return (0);
}
