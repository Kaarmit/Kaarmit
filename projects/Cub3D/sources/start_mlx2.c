/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_mlx2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 14:45:18 by aarmitan          #+#    #+#             */
/*   Updated: 2025/07/11 16:42:20 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	reset_screen(t_game *game)
{
	int	y;
	int	x;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			put_pixel(game, x, y, 0x00000000);
			x++;
		}
		y++;
	}
}

int	game_loop(t_game *game)
{
	handle_keys(game);
	reset_screen(game);
	background(game);
	raycasting(game);
	mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, game->m.img, 0, 0);
	return (0);
}
