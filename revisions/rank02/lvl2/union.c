/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   union.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 12:38:50 by aarmitan          #+#    #+#             */
/*   Updated: 2024/10/17 12:43:56 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unsitd.h>

int	main(int argc, char **argv)
{
	int	i = 0;
	int	j = 0;
	usigned char	seen[256] = {0};

	if (argc == 3)
	{
		while (argv[1][i])
		{
			if (!seen[(unsigned char)argv[1][i]])
			{
				write(1, &argv[1][i], 1);
				seen[(unsigned char)argv[1][i]] = 1;
			}
			i++;
		}
		while (argv[2][j])
		{
			if (!seen[(unsigned char)argv[2][j]])
			{
				write(1, &argv[2][j], 1);
				seen[(unsigned char)argv[2][j]] = 1;
			}
			j++;
		}
	}
	write(1, "\n", 1);
	return (0);
}
