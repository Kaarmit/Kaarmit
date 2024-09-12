/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_to.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 11:47:03 by aarmitan          #+#    #+#             */
/*   Updated: 2024/09/12 12:19:19 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	put_that_img(void *img, int x, int y, t_game *game)
{
	mlx_put_image_to_window(game->mlx_ptr, game->mlx_win, img, x * 50, y * 50);
}

int	is_wall(t_game *game, int y, int x)
{
	return (game->map[y][x] == '1');
}

void	*save_that_img(char *img_path, t_game *game)
{
	int	img_x;
	int	img_y;

	img_x = game->img_size.x;
	img_y = game->img_size.y;
	return (mlx_xpm_file_to_image(game->mlx_ptr, img_path, &img_x, &img_y));
}

void	move_to(int x, int y, void *dir, t_game *game)
{
	if (game->map[y][x] == 'E' && game->nb_c != 0)
		return ;
	put_that_img(game->bg_img, game->p_pos.x, game->p_pos.y, game);
	game->map[game->p_pos.y][game->p_pos.x] = '0';
	game->p_pos.y = y;
	game->p_pos.x = x;
	if (game->map[y][x] == 'C')
		game->nb_c--;
	put_that_img(dir, game->p_pos.x, game->p_pos.y, game);
	game->moves++;
	put_text(game);
	if (game->map[y][x] == 'E' && game->nb_c == 0)
		end_game("Congratulation you win!", game, event_end, NULL);
	game->map[y][x] = 'P';
	show_table(game->map);
}
