/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 13:01:04 by abastian          #+#    #+#             */
/*   Updated: 2025/07/11 17:09:34 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/cub3D_bonus.h"

int	is_forbidden(char data, char *allowed, t_game *game, int *flag)
{
	int	i;

	i = 0;
	while (allowed[i])
	{
		if (data == allowed[i])
		{
			if ((data == 'N' || data == 'S'
					|| data == 'E' || data == 'W') && (*flag) == 0)
			{
				(*flag) = 1;
				game->p.orientation = data;
			}
			else if ((data == 'N' || data == 'S'
					|| data == 'E' || data == 'W') && (*flag) == 1)
				error_game("Too many player positions in map", game);
			return (0);
		}
		i++;
	}
	return (1);
}

void	is_ok(char data, char *allowed, t_game *game)
{
	int	k;

	k = 0;
	while (allowed[k])
	{
		if (data == allowed[k])
			return ;
		k++;
	}
	error_game("Map is not enclosed by wall v2", game);
}

void	check_me(t_game *game, int i, int j)
{
	if ((i == 0 || j == 0)
		&& (game->grid[i][j] != ' ' && game->grid[i][j] != '1'))
		error_game("Map is not enclosed by wall v1", game);
	if (game->grid[i][j] == '0' || game->grid[i][j] == 'N' ||
		game->grid[i][j] == 'S' || game->grid[i][j] == 'E' ||
		game->grid[i][j] == 'W')
	{
		if (j != 0)
			is_ok(game->grid[i][j - 1], "10NSWE", game);
		if (i != 0)
			is_ok(game->grid[i - 1][j], "10NSWE", game);
		if (game->grid[i][j + 1])
			is_ok(game->grid[i][j + 1], "10NSWE", game);
		else
			error_game("Map is not enclosed by wall v3", game);
		if (game->grid[i + 1][j])
			is_ok(game->grid[i + 1][j], "10NSWE", game);
		else
			error_game("Map is not enclosed by wall v4", game);
	}
}

void	map_analyse(t_game *game, int i, int j, int flag)
{
	while (game->grid[i] && game->grid[i][0])
	{
		j = 0;
		while (game->grid[i][j])
		{
			if (is_forbidden(game->grid[i][j], " 10NSWE", game, &flag) == 1)
				error_game("Map is filled with forbidden data", game);
			j++;
		}
		i++;
	}
	if (flag == 0)
		error_game("Player position is missing", game);
	i = 0;
	while (game->grid[i] && game->grid[i][0])
	{
		j = 0;
		while (game->grid[i][j])
		{
			check_me(game, i, j);
			j++;
		}
		i++;
	}
	get_player_pos(game, 0, 0);
}

void	map_parse(char *map, t_game *game, int argc)
{
	char	*getmap;

	init_value(game);
	if (argc != 2)
		error_game("No or too many arguments found", game);
	if (!name_check(map))
		error_game("Wrong map format or no file's name (.cub needed).", game);
	getmap = get_map(map, game, NULL);
	if (!getmap)
		error_game("Could not get map", game);
	if (path_check(game))
		(free(getmap), error_game("At least one path is missing", game));
	if (game->doublepath != 0)
	{
		free(getmap);
		error_game("Double path detected and/or wrong texture extension", game);
	}
	if (each_line_check(getmap))
		(free(getmap), error_game("At least one map line is missing", game));
	game->grid = ft_split(getmap, '\n');
	free(getmap);
	height_value(game);
	if (!game->grid)
		error_game("Failed during split process", game);
	map_analyse(game, 0, 0, 0);
}
