/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_mlx.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 17:28:03 by abastian          #+#    #+#             */
/*   Updated: 2025/07/11 16:46:11 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	load_image(t_game *game, char *path, t_txtr *txtr)
{
	txtr->img = mlx_xpm_file_to_image(game->mlx_ptr, path,
			&txtr->width, &txtr->height);
	if (!txtr->img)
		error_game("Could not load texture into image", game);
	txtr->data = mlx_get_data_addr(txtr->img, &txtr->bpp,
			&txtr->size_line, &txtr->endian);
}

void	set_textures(t_game *game)
{
	load_image(game, game->nopath, &game->texture[TXTR_NO]);
	load_image(game, game->sopath, &game->texture[TXTR_SO]);
	load_image(game, game->wepath, &game->texture[TXTR_WE]);
	load_image(game, game->eapath, &game->texture[TXTR_EA]);
}

int	end(t_game *game)
{
	game_over(game, 0);
	return (0);
}

void	two_dimension_init(t_game *game)
{
	game->m.img = mlx_new_image(game->mlx_ptr, WIDTH, HEIGHT);
	if (!game->m.img)
		error_game("fatal_error image", game);
	game->m.data = mlx_get_data_addr(game->m.img, &game->m.bpp,
			&game->m.size_line, &game->m.endian);
	if (!game->m.data)
		error_game("fatal error data", game);
}

void	start_mlx(t_game *game)
{
	if (game->errcolor != 0)
		error_game("Invalid color format", game);
	game->mlx_ptr = mlx_init();
	if (!game->mlx_ptr)
		error_game("Could not initiate the first mlx pointer", game);
	game->win_ptr = mlx_new_window(game->mlx_ptr, WIDTH, HEIGHT, "cub3D");
	if (!game->win_ptr)
		error_game("Could not create window", game);
	set_textures(game);
	init_player(&game->p, game->p.orientation);
	two_dimension_init(game);
	mlx_hook(game->win_ptr, 2, 1L << 0, key_press, game);
	mlx_hook(game->win_ptr, 3, 1L << 1, key_release, game);
	mlx_hook(game->win_ptr, 17, 0, &end, game);
	mlx_loop_hook(game->mlx_ptr, game_loop, game);
	mlx_loop(game->mlx_ptr);
}
