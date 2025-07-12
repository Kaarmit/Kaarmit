/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2Dview.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 12:13:21 by abastian          #+#    #+#             */
/*   Updated: 2025/07/12 15:03:01 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/cub3D_bonus.h"

static void	calc_tile_size(t_game *g, int *tile)
{
	int	w;
	int	h;
	int	x;
	int	y;

	x = 0;
	while (g->grid[x])
		x++;
	y = ft_strlen(g->grid[0]);
	w = 200 / y;
	h = 200 / x;
	if (w < h)
		*tile = w;
	else
		*tile = h;
}

void	set_map(t_game *g, int x, int y, int tile)
{
	int	color;
	int	dx;
	int	dy;

	while (g->grid[y])
	{
		x = 0;
		while (g->grid[y][x])
		{
			if (g->grid[y][x] == '1')
				color = 0x00666666;
			else
				color = 0x00000000;
			dy = 0;
			while (dy < tile)
			{
				dx = 0;
				while (dx++ < tile)
					put_pixel(g, x * tile + dx, y * tile + dy, color);
				dy++;
			}
			x++;
		}
		y++;
	}
}

void	set_player(t_game *g, int size, int y, int tile)
{
	int	px;
	int	py;
	int	x;

	while (y < size * 2 + 1)
	{
		x = 0;
		while (x < size * 2 + 1)
		{
			px = (int)(g->p.x * tile) - size + x;
			py = (int)(g->p.y * tile) - size + y;
			put_pixel(g, px, py, 0x00FF0000);
			x++;
		}
		y++;
	}
}

void	set_direction(t_game *game, int i, double x, double y)
{
	int		len;
	double	dy;
	double	dx;
	int		px;
	int		py;

	len = 16;
	dx = game->p.dir_x;
	dy = game->p.dir_y;
	while (i < len)
	{
		px = (int)(x + dx * i);
		py = (int)(y + dy * i);
		put_pixel(game, px, py, 0x00FF0000);
		i++;
	}
}

int	minimap(t_game *game)
{
	int	tile;

	calc_tile_size(game, &tile);
	set_map(game, 0, 0, tile);
	set_player(game, 4, 0, tile);
	set_direction(game, 0, game->p.x * tile, game->p.y * tile);
	return (0);
}
