/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 11:02:17 by aarmitan          #+#    #+#             */
/*   Updated: 2024/09/13 14:33:38 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

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
		end_game(ERRSAVE, game, map_error, NULL);
	collected = fill(map_clone, game->map_size, game->p_pos, "CP0");
	free_map(map_clone);
	if (collected == game->nb_c)
	{
		map_clone = get_map(map_file, game, err);
		if (!map_clone)
			end_game(ERRSAVE1, game, map_error, NULL);
		collected = fill(map_clone, game->map_size, game->p_pos, "ECP0");
		free_map(map_clone);
	}
	if (collected != game->nb_c + 1)
		end_game(ERRMAP, game, map_error, NULL);
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
				end_game(ERRECT, game, map_error, NULL);
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
		end_game(ERRWALLS, game, map_error, NULL);
	i = game->map_size.y - 1;
	while (i)
	{
		end = ft_strlen(game->map[i]) - 1;
		if (!is_wall(game, i, 0) || !is_wall(game, i, end))
			end_game(ERRWALLS, game, map_error, NULL);
		i--;
	}
	if (check_line(game->map[game->map_size.y - 1]))
		end_game(ERRWALLS, game, map_error, NULL);
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
			else if (game->map[map->y][map->x] != '1')
				if (game->map[map->y][map->x] != '0')
					end_game(UNKNOWN, game, map_error, NULL);
			map->x++;
		}
	}
	if (game->nb_c < 1 || map->e != 1)
		end_game(ERRELEM, game, map_error, NULL);
	else if (map->p != 1)
		end_game(ERRPLAYER, game, map_error, NULL);
}
