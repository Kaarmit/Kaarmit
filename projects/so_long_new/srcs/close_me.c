/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_me.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 11:38:59 by aarmitan          #+#    #+#             */
/*   Updated: 2024/09/12 12:17:48 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"
#include <mlx.h>

int	exit_event(t_game *game)
{
	end_game("", game, event_end, NULL);
	return (0);
}

void	free_map(char **map)
{
	int	i;

	i = 0;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
	return;
}


void	destroy_the(t_game *game)
{
	mlx_destroy_image(game->mlx_ptr, game->wall_img);
	mlx_destroy_image(game->mlx_ptr, game->bg_img);
	mlx_destroy_image(game->mlx_ptr, game->pac_img_u);
	mlx_destroy_image(game->mlx_ptr, game->pac_img_d);
	mlx_destroy_image(game->mlx_ptr, game->pac_img_l);
	mlx_destroy_image(game->mlx_ptr, game->pac_img_r);
	mlx_destroy_image(game->mlx_ptr, game->collec_img);
	mlx_destroy_image(game->mlx_ptr, game->exit_img);
	mlx_destroy_window(game->mlx_ptr, game->mlx_win);
	mlx_destroy_display(game->mlx_ptr);
	free_map(game->map);
	free(game->mlx_ptr);
	return ;
}

void	end_game(char *msg, t_game *game, enum e_state state, char *free_me)
{
	if (state == event_end)
	{
		ft_printf("%s\n", msg);
		destroy_the(game);
		exit(0);
	}
	else if (state == file_error)
	{
		ft_printf("Error\n__FILE_ERROR__ : %s\n", msg);
		if (free_me != NULL)
			free(free_me);
		exit(1);
	}
	else if (state == map_error)
	{
		ft_printf("Error\n__MAP_ERROR__ : %s\n", msg);
		free_map(game->map);
		if (free_me != NULL)
			free(free_me);
		exit(2);
	}
	ft_printf("Error\n%s\n", msg);
	destroy_the(game);
	exit(3);
}
