/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 13:07:47 by aarmitan          #+#    #+#             */
/*   Updated: 2024/08/22 14:46:17 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

int	fill(char **map, t_vector size, t_vector cur, char *e)
{
	static int	elem_count = 0;

	if (is_out(cur.x, cur.y, size.x, size.y) || !to_find(e, map[cur.y][cur.x]))
		return (elem_count);
	if (map[cur.y][cur.x] == e[0])
		elem_count++;
	map[cur.y][cur.x] = 'X';
	fill(map, size, (t_vector){cur.x - 1, cur.y}, e);
	fill(map, size, (t_vector){cur.x + 1, cur.y}, e);
	fill(map, size, (t_vector){cur.x, cur.y - 1}, e);
	fill(map, size, (t_vector){cur.x, cur.y + 1}, e);
	return (elem_count);
}

void	is_map_playable(t_game *game, char *map_file, int err)
{
	char	**map_clone;
	int		collected;

	map_clone = get_map(map_file, game, err);
	if (!map_clone)
		end_game("An error occurred saving the map.", game, map_error, NULL);
	collected = fill(map_clone, game->map_size, game->p_pos, "CP0");
	free_map(map_clone);
	if (collected == game->nb_c)
	{
		map_clone = get_map(map_file, game, err);
		if (!map_clone)
			end_game("Could not save the map.", game, map_error, NULL);
		collected = fill(map_clone, game->map_size, game->p_pos, "ECP0");
		free_map(map_clone);
	}
	if (collected != game->nb_c + 1)
		end_game("Unplayable map. Aborting, bye!", game, map_error, NULL);
	return ;
}

void	check_map_rect(t_game *game)
{
	int	y;
	int	x;
	int	height;
	int	temp;

	y = 0;
	temp = 0;
	height = game->map_size.y;
	while (y != height)
	{
		x = 0;
		while (game->map[y][x] != '\0')
			x++;
		y++;
		if (temp != 0)
		{
			if (temp != x)
				end_game("This map is not rectangular!", game, map_error, NULL);
		}
		else
			temp = x;
	}
}

void	check_map_walls(t_game *game)
{
	int	i;
	int	end;

	if (check_line(game->map[0]))
		end_game("Map not surrounded by walls!", game, map_error, NULL);
	i = game->map_size.y - 1;
	while (i)
	{
		end = ft_strlen(game->map[i]) - 1;
		if (!is_wall(game, i, 0) || !is_wall(game, i, end))
			end_game("Map not surrounded by walls!", game, map_error, NULL);
		i--;
	}
	if (check_line(game->map[game->map_size.y - 1]))
		end_game("Map not surrounded by walls!", game, map_error, NULL);
}

void	check_map_elem(t_game *game, t_game_map *map)
{
	while (map->y--)
	{
		map->x = 0;
		while (game->map[map->y][map->x] != '\0')
		{
			if (game->map[map->y][map->x] == 'E')
				map->e++;
			else if (game->map[map->y][map->x] == 'P')
			{
				map->p++;
				game->p_pos.x = map->x;
				game->p_pos.y = map->y;
			}
			else if (game->map[map->y][map->x] == 'C')
				game->nb_c++;
			else if (game->map[map->y][map->x] == 'B')
				map->b++;
			else if (game->map[map->y][map->x] != '1')
				if (game->map[map->y][map->x] != '0')
					end_game("Unknown element.", game, map_error, NULL);
			map->x++;
		}
	}
	if (game->nb_c < 1 || map->p != 1 || map->e != 1 || map->b < 1)
		end_game("Wrong number of elements", game, map_error, NULL);
}
