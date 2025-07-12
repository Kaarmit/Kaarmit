/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 14:39:11 by aarmitan          #+#    #+#             */
/*   Updated: 2025/07/11 17:20:08 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/cub3D_bonus.h"

int	key_press(int keycode, t_game *game)
{
	if (keycode == XK_w)
		game->keys.w = 1;
	else if (keycode == XK_s)
		game->keys.s = 1;
	else if (keycode == XK_a)
		game->keys.a = 1;
	else if (keycode == XK_d)
		game->keys.d = 1;
	else if (keycode == XK_Left)
		game->keys.left = 1;
	else if (keycode == XK_Right)
		game->keys.right = 1;
	else if (keycode == XK_Escape)
		end(game);
	return (0);
}

int	key_release(int keycode, t_game *game)
{
	if (keycode == XK_w)
		game->keys.w = 0;
	else if (keycode == XK_s)
		game->keys.s = 0;
	else if (keycode == XK_a)
		game->keys.a = 0;
	else if (keycode == XK_d)
		game->keys.d = 0;
	else if (keycode == XK_Left)
		game->keys.left = 0;
	else if (keycode == XK_Right)
		game->keys.right = 0;
	return (0);
}

void	rotate_left(t_play *p)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = p->dir_x;
	p->dir_x = p->dir_x * cos(-p->rot_speed) - p->dir_y * sin(-p->rot_speed);
	p->dir_y = old_dir_x * sin(-p->rot_speed) + p->dir_y * cos(-p->rot_speed);
	old_plane_x = p->plane_x;
	p->plane_x = p->plane_x * cos(-p->rot_speed) - p->plane_y
		* sin(-p->rot_speed);
	p->plane_y = old_plane_x * sin(-p->rot_speed) + p->plane_y
		* cos(-p->rot_speed);
}

void	rotate_right(t_play *p)
{
	double	old_plane_x;
	double	old_dir_x;

	old_dir_x = p->dir_x;
	p->dir_x = p->dir_x * cos(p->rot_speed) - p->dir_y * sin(p->rot_speed);
	p->dir_y = old_dir_x * sin(p->rot_speed) + p->dir_y * cos(p->rot_speed);
	old_plane_x = p->plane_x;
	p->plane_x = p->plane_x * cos(p->rot_speed) - p->plane_y
		* sin(p->rot_speed);
	p->plane_y = old_plane_x * sin(p->rot_speed) + p->plane_y
		* cos(p->rot_speed);
}

int	handle_keys(t_game *g)
{
	if (g->keys.w)
		move_forward_bonus(&g->p, g->grid);
	if (g->keys.s)
		move_backward_bonus(&g->p, g->grid);
	if (g->keys.a)
		move_left_bonus(&g->p, g->grid);
	if (g->keys.d)
		move_right_bonus(&g->p, g->grid);
	if (g->keys.left)
		rotate_left(&g->p);
	if (g->keys.right)
		rotate_right(&g->p);
	return (0);
}
