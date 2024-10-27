/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 11:36:42 by aarmitan          #+#    #+#             */
/*   Updated: 2024/10/17 11:41:31 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int	main(int argc, char **argv)
{
	int				i;
	int				j;
	unsigned char	seen[256] = {0};

	if (argc == 3)
	{
		i = 0;
		while (argv[1][i])
		{
			while (argv[2][j])
			{
				if (argv[1][i] == argv[2][j])
				{
					if (!seen[(unsigned char)argv[1][i]])
					{
						write(1, &argv[1][i], 1);
						seen[(unsigned char)argv[1][i]] = 1;
					}
					break ;
				}
				j++;
			}
			i++;
		}
	}
	write(1, "\n", 1);
	return (0);
}
