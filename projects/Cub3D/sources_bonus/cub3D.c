/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 12:44:47 by abastian          #+#    #+#             */
/*   Updated: 2025/07/11 17:09:22 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/cub3D_bonus.h"

int	main(int argc, char **argv)
{
	t_game	game;

	map_parse(argv[1], &game, argc);
	start_mlx(&game);
	error_game("c'est passe", &game);
	return (0);
}
