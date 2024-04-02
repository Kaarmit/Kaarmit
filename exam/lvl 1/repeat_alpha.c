/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   repeat_alpha.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 12:51:31 by aarmitan          #+#    #+#             */
/*   Updated: 2024/03/30 14:45:20 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int	main(int argc, char **argv)
{
	int	repeat;
	int	i;

	if(argc != 2)
		write(1, "\n", 1);
	i = 0;
	repeat = 1;
	while (argv[1][i] != '\0')
	{
		if ((argv[1][i] >= 'a') && (argv[1][i] <= 'z'))
		{
			repeat += argv[1][i] - 'a';
		}
		else if ((argv [1][i] >= 'A') && (argv[1][i]))
		{
			repeat += argv[1][i] - 'A';
		}
		while(repeat)
		{
			write(1, &argv[1][i], 1);
			repeat--;
		}
		i++;
	}
}
