/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 14:55:26 by aarmitan          #+#    #+#             */
/*   Updated: 2025/07/11 16:47:22 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	is_out(char data, char *allowed, t_game *game)
{
	int	k;

	k = 0;
	while (allowed[k])
	{
		if (data == allowed[k])
			error_game("You exited the map", game);
		k++;
	}
}

void	check_out(t_game *game, int i, int j)
{
	if ((i == 0 || j == 0))
		error_game("You exited the map", game);
	if (j != 0)
		is_out(game->grid[i][j - 1], " \t", game);
	if (i != 0)
		is_out(game->grid[i - 1][j], " \t", game);
	if (game->grid[i][j + 1])
		is_out(game->grid[i][j + 1], " \t", game);
	else
		error_game("You exited the map", game);
	if (i + 1 < game->map_height && game->grid[i + 1][j])
		is_out(game->grid[i + 1][j], " \t", game);
	else
		error_game("You exited the map", game);
}
