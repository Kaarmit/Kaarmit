/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aff_z.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 16:03:07 by aarmitan          #+#    #+#             */
/*   Updated: 2024/04/04 16:05:28 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	affZ(void)
{
	write(1, "z\n", 2);
}

int	main(int argc, char **argv)
{
	(void) argc;
	(void) argv;
	affZ();
}
