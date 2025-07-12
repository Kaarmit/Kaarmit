/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 14:35:06 by aarmitan          #+#    #+#             */
/*   Updated: 2025/07/11 14:55:48 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	move_forward(t_play *p, t_game *game)
{
	check_out(game, (int)(p->y + p->dir_y * p->move_speed), (int)(p->x
			+ p->dir_x * p->move_speed));
	p->x += p->dir_x * p->move_speed;
	p->y += p->dir_y * p->move_speed;
}

void	move_backward(t_play *p, t_game *game)
{
	check_out(game, (int)(p->y), (int)(p->x + p->dir_x * p->move_speed));
	p->x -= p->dir_x * p->move_speed;
	p->y -= p->dir_y * p->move_speed;
}

void	move_right(t_play *p, t_game *game)
{
	check_out(game, (int)(p->y), (int)(p->x + p->dir_x * p->move_speed));
	p->x += p->plane_x * p->move_speed;
	p->y += p->plane_y * p->move_speed;
}

void	move_left(t_play *p, t_game *game)
{
	check_out(game, (int)(p->y), (int)(p->x + p->dir_x * p->move_speed));
	p->x -= p->plane_x * p->move_speed;
	p->y -= p->plane_y * p->move_speed;
}
