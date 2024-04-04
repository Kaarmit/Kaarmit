/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_op.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 16:20:57 by aarmitan          #+#    #+#             */
/*   Updated: 2024/04/04 16:41:45 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int	main(int argc, char **argv)
{
	int	nb = 0;
	int	nb2 = 0;
	int	result = 0;

	if (argc != 4)
		write(1, "\n", 1);
	else if (argc == 4)
	{
		nb = atoi(argv[1]);
		nb2 = atoi(argv[3]);
		if (*argv[2]== '+')
			result = nb + nb2;
		if (*argv[2] == '-')
			result = nb - nb2;
		if (*argv[2] == '*')
			result = nb * nb2;
		if (*argv[2] == '/')
			result = nb / nb2;
		printf("%d\n", result);	
	}
}
