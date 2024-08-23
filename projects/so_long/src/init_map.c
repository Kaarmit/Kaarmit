/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 14:56:16 by aarmitan          #+#    #+#             */
/*   Updated: 2024/08/23 15:51:21 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"


void	img_on_map(char p, int x, int y, t_game *g)
{
	if (p == '1')
		mlx_put_image_to_window(g->mlx_ptr, g->mlx_win, g->wall_img, x, y);
	else if (p == 'C')
		mlx_put_image_to_window(g->mlx_ptr, g->mlx_win, g->collec_img, x, y);
	else if (p == 'E')
		mlx_put_image_to_window(g->mlx_ptr, g->mlx_win, g->exit_img, x, y);
	else if (p == 'P')
		mlx_put_image_to_window(g->mlx_ptr, g->mlx_win, g->pac_img, x, y);
	else if (p == 'B')
		mlx_put_image_to_window(g->mlx_ptr, g->mlx_win, g->enemy_B_img, x, y);
	else if (p == 'R')
		mlx_put_image_to_window(g->mlx_ptr, g->mlx_win, g->enemy_R_img, x, y);
	else if (p == 'G')
		mlx_put_image_to_window(g->mlx_ptr, g->mlx_win, g->enemy_G_img, x, y);
	else if (p == 'P')
		mlx_put_image_to_window(g->mlx_ptr, g->mlx_win, g->enemy_P_img, x, y);
	else
		mlx_put_image_to_window(g->mlx_ptr, g->mlx_win, g->bg_img, x, y);
}

void	*save_that_img(char *img_path, t_game *game)
{
	int	img_x;
	int	img_y;

	img_x = game->img_size.x;
	img_y = game->img_size.y;
	return(mlx_xpm_file_to_image(game->mlx_ptr, img_path, &img_x, &img_y));
}

void	init_img(t_game *game)
{
	game->pac_img = save_that_img("../assets/pac.xpm", game);
	game->wall_img = save_that_img("../assets/wall.xpm", game);
	game->collec_img = save_that_img("../assets/collec.xpm", game);
	game->enemy_B_img = save_that_img("../assets/ghost_blue.xpm", game);
	game->enemy_G_img = save_that_img("../assets/ghost_green.xpm", game);
	game->enemy_R_img = save_that_img("../assets/ghost_pink.xpm", game);
	game->enemy_P_img = save_that_img("../assets/ghost_purple.xpm", game);
	game->exit_img = save_that_img("../assets/exit.xpm", game);
	game->bg_img = save_that_img("../assets/black.xpm", game);
}


void	update_values(int *map_x, int *x, int *map_size_x)
{
	(*map_x)++;
	*x += 50;
	(*map_size_x)--;
}

void	render_map(t_game *game)
{
	int	y;
	int	x;
	int	map_y;
	int	map_x;
	int	tmp_w;

	y = 0;
	map_y = 0;
	tmp_w = game->map_size.x;
	init_img(game);
	while (game->map_size.y > 0)
	{
		x = 0;
		map_x = 0;
		while (game->map_size.x > 0)
		{
			img_on_map(game->map[map_y][map_x], x, y, game);
			update_values(&map_x, &x, &game->map_size.x);
		}
		game->map_size.x = tmp_w;
		map_y++;
		y += 50;
		game->map_size.y--;
	}
}



