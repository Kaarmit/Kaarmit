/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 15:04:58 by aarmitan          #+#    #+#             */
/*   Updated: 2025/07/11 16:44:06 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	get_player_pos(t_game *game, int i, int j)
{
	while (game->grid[i] && game->grid[i][0])
	{
		j = 0;
		while (game->grid[i][j])
		{
			if (game->grid[i][j] == game->p.orientation)
			{
				game->p.x = j + 0.5;
				game->p.y = i + 0.5;
				return ;
			}
			j++;
		}
		i++;
	}
	error_game("Error parsing, cannot find player position", game);
}

void	init_player_next(t_play *p, char dir)
{
	if (dir == 'E')
	{
		p->dir_x = 1;
		p->dir_y = 0;
		p->plane_x = 0;
		p->plane_y = 0.66;
	}
	else if (dir == 'W')
	{
		p->dir_x = -1;
		p->dir_y = 0;
		p->plane_x = 0;
		p->plane_y = -0.66;
	}
}

void	init_player(t_play *p, char dir)
{
	if (dir == 'N')
	{
		p->dir_x = 0;
		p->dir_y = -1;
		p->plane_x = 0.66;
		p->plane_y = 0;
	}
	else if (dir == 'S')
	{
		p->dir_x = 0;
		p->dir_y = 1;
		p->plane_x = -0.66;
		p->plane_y = 0;
	}
	else
		init_player_next(p, dir);
	p->move_speed = 0.10;
	p->rot_speed = 0.05;
}
