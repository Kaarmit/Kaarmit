/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 14:35:06 by aarmitan          #+#    #+#             */
/*   Updated: 2025/07/11 17:28:07 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/cub3D_bonus.h"

int	is_wall_near(char **map, double x, double y)
{
	int	ix;
	int	iy;

	ix = (int)x;
	iy = (int)y;
	if (map[iy][ix] == '1')
		return (1);
	if (map[(int)(y + 0.2)][ix] == '1')
		return (1);
	if (map[(int)(y - 0.2)][ix] == '1')
		return (1);
	if (map[iy][(int)(x + 0.2)] == '1')
		return (1);
	if (map[iy][(int)(x - 0.2)] == '1')
		return (1);
	if (map[(int)(y + 0.2)][(int)(x + 0.2)] == '1')
		return (1);
	if (map[(int)(y + 0.2)][(int)(x - 0.2)] == '1')
		return (1);
	if (map[(int)(y - 0.2)][(int)(x + 0.2)] == '1')
		return (1);
	if (map[(int)(y - 0.2)][(int)(x - 0.2)] == '1')
		return (1);
	return (0);
}

void	move_forward_bonus(t_play *p, char **map)
{
	double	next_x;
	double	next_y;

	next_x = p->x + p->dir_x * p->move_speed;
	next_y = p->y + p->dir_y * p->move_speed;
	if (!is_wall_near(map, next_x, p->y))
		p->x = next_x;
	if (!is_wall_near(map, p->x, next_y))
		p->y = next_y;
}

void	move_backward_bonus(t_play *p, char **map)
{
	double	next_x;
	double	next_y;

	next_x = p->x - p->dir_x * p->move_speed;
	next_y = p->y - p->dir_y * p->move_speed;
	if (!is_wall_near(map, next_x, p->y))
		p->x = next_x;
	if (!is_wall_near(map, p->x, next_y))
		p->y = next_y;
}

void	move_right_bonus(t_play *p, char **map)
{
	double	next_x;
	double	next_y;

	next_x = p->x + p->plane_x * p->move_speed;
	next_y = p->y + p->plane_y * p->move_speed;
	if (!is_wall_near(map, next_x, p->y))
		p->x = next_x;
	if (!is_wall_near(map, p->x, next_y))
		p->y = next_y;
}

void	move_left_bonus(t_play *p, char **map)
{
	double	next_x;
	double	next_y;

	next_x = p->x - p->plane_x * p->move_speed;
	next_y = p->y - p->plane_y * p->move_speed;
	if (!is_wall_near(map, next_x, p->y))
		p->x = next_x;
	if (!is_wall_near(map, p->x, next_y))
		p->y = next_y;
}
