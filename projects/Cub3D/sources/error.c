/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 12:55:57 by abastian          #+#    #+#             */
/*   Updated: 2025/07/11 14:36:01 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	destroy_textures(t_game *game)
{
	int	i;

	i = 0;
	while (i < NB_TXTR)
	{
		if (game->texture[i].img != NULL)
			mlx_destroy_image(game->mlx_ptr, game->texture[i].img);
		i++;
	}
}

void	destroy_all(t_game *game)
{
	if (game->grid != NULL)
		freegrid(game->grid);
	if (game->nopath != NULL)
		free(game->nopath);
	if (game->sopath != NULL)
		free(game->sopath);
	if (game->wepath != NULL)
		free(game->wepath);
	if (game->eapath != NULL)
		free(game->eapath);
	if (game->trim != NULL)
		free(game->trim);
	if (game->m.img != NULL)
		mlx_destroy_image(game->mlx_ptr, game->m.img);
	destroy_textures(game);
	if (game->win_ptr != NULL)
		mlx_destroy_window(game->mlx_ptr, game->win_ptr);
	if (game->mlx_ptr != NULL)
	{
		mlx_destroy_display(game->mlx_ptr);
		free(game->mlx_ptr);
	}
}

void	error_game(char *message, t_game *game)
{
	printf("Error\n%s\n", message);
	destroy_all(game);
	exit(EXIT_FAILURE);
}

void	init_textures(t_game *game)
{
	int	i;

	i = 0;
	while (i < NB_TXTR)
	{
		game->texture[i].img = NULL;
		game->texture[i].data = NULL;
		game->texture[i].width = 0;
		game->texture[i].height = 0;
		game->texture[i].bpp = 0;
		game->texture[i].size_line = 0;
		game->texture[i].endian = 0;
		i++;
	}
}

void	init_value(t_game *game)
{
	game->grid = NULL;
	game->win_ptr = NULL;
	game->mlx_ptr = NULL;
	game->nopath = NULL;
	game->sopath = NULL;
	game->wepath = NULL;
	game->eapath = NULL;
	game->trim = NULL;
	game->fcolor = -1;
	game->ccolor = -1;
	game->m.img = NULL;
	game->m.data = NULL;
	game->doublepath = 0;
	game->errcolor = 0;
	game->keys.w = 0;
	game->keys.a = 0;
	game->keys.s = 0;
	game->keys.d = 0;
	game->keys.left = 0;
	game->keys.right = 0;
	game->r.hit = 0;
	game->p.orientation = '\0';
	init_textures(game);
}
