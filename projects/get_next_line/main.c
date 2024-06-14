/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 18:13:09 by aarmitan          #+#    #+#             */
/*   Updated: 2024/06/13 18:15:38 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>

int	main(void)
{
	int	fd;

	fd = open("fichier.txt", O_RDONLY);
	while (fd)
	{
		get_next_line(fd);
		fd--;
	}
	close(fd);
	return (0);
}
