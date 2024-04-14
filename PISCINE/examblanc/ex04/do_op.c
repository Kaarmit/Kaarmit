/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_op.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 11:21:46 by aarmitan          #+#    #+#             */
/*   Updated: 2024/04/02 11:50:52 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int	main(int argc, char **argv)
{
	int	result = 0;
	int	i = 0;
	int	sign = 0;
	int	a = 0;
	int	b = 0;

	if (argc == 4)
	{
		while (argv[1] && argv[1][i] >= '0' && argv[1][i] <= '9')
		{
			//atoi(argv[1][i]);
			i++;
		}
		a = atoi(argv[1]);
		while (argv[3] && argv[3][i] >= '0' && argv[3][i] <= '9')
		{
		//	atoi(argv[3]);
			i++;
		}
		b = atoi(argv[3]);
		if (argv[2][sign] == '+')
			result = a + b;
		if (argv[2][sign] == '-')
                         result = a - b;
		if (argv[2][sign] == '/')
                         result = a / b;
		if (argv[2][sign] == '%')
                         result = a % b;
	}
	printf("%d", result);
	return (result);
}

