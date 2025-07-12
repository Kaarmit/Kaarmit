/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 17:25:59 by abastian          #+#    #+#             */
/*   Updated: 2025/07/11 16:36:19 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	put_pixel(t_game *game, int x, int y, int color)
{
	int	offset;

	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return ;
	offset = y * game->m.size_line + x * (game->m.bpp / 8);
	game->m.data[offset] = color & 0xFF;
	game->m.data[offset + 1] = (color >> 8) & 0xFF;
	game->m.data[offset + 2] = (color >> 16) & 0xFF;
}

void	background(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			if (y < HEIGHT / 2)
				put_pixel(game, x, y, game->ccolor);
			else
				put_pixel(game, x, y, game->fcolor);
			x++;
		}
		y++;
	}
}

void	which_one(t_game *g)
{
	if (g->r.side == 0 && g->r.ray_dir_x < 0)
		g->r.that_one = TXTR_WE;
	else if (g->r.side == 0 && g->r.ray_dir_x >= 0)
		g->r.that_one = TXTR_EA;
	else if (g->r.side == 1 && g->r.ray_dir_y < 0)
		g->r.that_one = TXTR_NO;
	else
		g->r.that_one = TXTR_SO;
}

void	render_next(t_game *g)
{
	double	temp;

	if (g->r.side == 0)
		g->r.wall_x = g->p.y + g->r.perp_wall_dist * g->r.ray_dir_y;
	else
		g->r.wall_x = g->p.x + g->r.perp_wall_dist * g->r.ray_dir_x;
	temp = g->r.wall_x;
	g->r.wall_x -= floor(temp);
	g->r.tex_x = (int)(g->r.wall_x * (double)g->texture[g->r.that_one].width);
	if ((g->r.side == 0 && g->r.ray_dir_x < 0)
		|| (g->r.side == 1 && g->r.ray_dir_y > 0))
		g->r.tex_x = g->texture[g->r.that_one].width - g->r.tex_x - 1;
	if (g->r.tex_x < 0)
		g->r.tex_x = 0;
	else if (g->r.tex_x >= g->texture[g->r.that_one].width)
		g->r.tex_x = g->texture[g->r.that_one].width - 1;
}

void	render_texture(t_game *g, int x)
{
	int	y;

	which_one(g);
	render_next(g);
	y = g->r.draw_start;
	while (y <= g->r.draw_end)
	{
		g->r.d = y * 256 - HEIGHT * 128 + g->r.line_height * 128;
		g->r.tex_y = ((g->r.d * g->texture[g->r.that_one].height)
				/ g->r.line_height) / 256;
		if (g->r.tex_y < 0)
			g->r.tex_y = 0;
		else if (g->r.tex_y >= g->texture[g->r.that_one].height)
			g->r.tex_y = g->texture[g->r.that_one].height - 1;
		g->r.color = *(unsigned int *)(g->texture[g->r.that_one].data
				+ g->r.tex_y * g->texture[g->r.that_one].size_line
				+ g->r.tex_x * (g->texture[g->r.that_one].bpp / 8));
		put_pixel(g, x, y, g->r.color);
		y++;
	}
}
