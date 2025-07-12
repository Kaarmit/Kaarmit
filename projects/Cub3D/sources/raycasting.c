/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 14:37:58 by abastian          #+#    #+#             */
/*   Updated: 2025/07/11 14:55:01 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	values_next(t_game *g)
{
	if (g->r.ray_dir_x < 0)
	{
		g->r.step_x = -1;
		g->r.side_dist_x = (g->p.x - g->r.map_x) * g->r.delta_dist_x;
	}
	else
	{
		g->r.step_x = 1;
		g->r.side_dist_x = (g->r.map_x + 1 - g->p.x) * g->r.delta_dist_x;
	}
	if (g->r.ray_dir_y < 0)
	{
		g->r.step_y = -1;
		g->r.side_dist_y = (g->p.y - g->r.map_y) * g->r.delta_dist_y;
	}
	else
	{
		g->r.step_y = 1;
		g->r.side_dist_y = (g->r.map_y + 1 - g->p.y) * g->r.delta_dist_y;
	}
}

void	reset_values(t_game *g, int x)
{
	g->r.camera_x = 2.0 * x / WIDTH - 1;
	g->r.ray_dir_x = g->p.dir_x + g->p.plane_x * g->r.camera_x;
	g->r.ray_dir_y = g->p.dir_y + g->p.plane_y * g->r.camera_x;
	g->r.map_x = (int)g->p.x;
	g->r.map_y = (int)g->p.y;
	if (g->r.ray_dir_x == 0)
		g->r.delta_dist_x = 1e30;
	else
		g->r.delta_dist_x = fabs(1.0 / g->r.ray_dir_x);
	if (g->r.ray_dir_y == 0)
		g->r.delta_dist_y = 1e30;
	else
		g->r.delta_dist_y = fabs(1.0 / g->r.ray_dir_y);
	values_next(g);
}

void	distance_wall(t_game *g)
{
	if (g->r.side == 0)
		g->r.perp_wall_dist = (g->r.map_x - g->p.x
				+ (1 - g->r.step_x) / 2) / g->r.ray_dir_x;
	else
		g->r.perp_wall_dist = (g->r.map_y - g->p.y
				+ (1 - g->r.step_y) / 2) / g->r.ray_dir_y;
	g->r.line_height = (int)(HEIGHT / g->r.perp_wall_dist);
	g->r.draw_start = (g->r.line_height * -1) / 2 + HEIGHT / 2;
	if (g->r.draw_start < 0)
		g->r.draw_start = 0;
	g->r.draw_end = g->r.line_height / 2 + HEIGHT / 2;
	if (g->r.draw_end >= HEIGHT)
		g->r.draw_end = HEIGHT - 1;
}

void	dda_hit(t_game *g)
{
	while (g->r.hit == 0)
	{
		if (g->r.side_dist_x < g->r.side_dist_y)
		{
			g->r.side_dist_x += g->r.delta_dist_x;
			g->r.map_x += g->r.step_x;
			g->r.side = 0;
		}
		else
		{
			g->r.side_dist_y += g->r.delta_dist_y;
			g->r.map_y += g->r.step_y;
			g->r.side = 1;
		}
		if (g->r.map_y < 0 || g->r.map_y >= g->map_height
			|| g->r.map_x < 0 || !g->grid[g->r.map_y]
			|| g->r.map_x >= (int)ft_strlen(g->grid[g->r.map_y]))
			error_game("You exited the map", g);
		if (g->grid[g->r.map_y][g->r.map_x] == '1')
			g->r.hit = 1;
	}
}

void	raycasting(t_game *g)
{
	int	x;
	int	y;

	x = 0;
	while (x < WIDTH)
	{
		g->r.hit = 0;
		reset_values(g, x);
		dda_hit(g);
		distance_wall(g);
		render_texture(g, x);
		x++;
	}
}
