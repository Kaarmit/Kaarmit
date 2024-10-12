/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   epur_str.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 18:35:08 by aarmitan          #+#    #+#             */
/*   Updated: 2024/10/09 18:40:37 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int	main(int argc, char const **argv)
{
	int	i;
	int	flg;

	if (argc == 2)
	{
		i = 0;
		while (argv[1][i] == ' ' || argv[1][i] == '\t')
			i += 1;
		while (argv[1][i])
		{
			if (argv[1][i] == ' ' || argv[1][i] == '\t')
				flg = 1;
			if (!(argv[1][i] == ' ' || argv[1][i] == '\t'))
			{
				if (flg)
					write(1, " ", 1);
				flg = 0;
				write(1, &argv[1][i], 1);
			}
			i += 1;
		}
	}
	write(1, "\n", 1);
	return (0);
}
