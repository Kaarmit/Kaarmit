/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 14:57:07 by aarmitan          #+#    #+#             */
/*   Updated: 2025/07/12 16:02:14 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	height_value(t_game *game)
{
	int	i;

	i = 0;
	while (game->grid[i])
		i++;
	game->map_height = i;
}

void	split_check(char **split, t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (split[i])
	{
		j = 0;
		while (split[i][j])
		{
			if (!ft_isdigit(split[i][j]))
				game->errcolor++;
			j++;
		}
		if (j > 3)
			game->errcolor++;
		if (j > 1 && split[i][0] == '0')
			game->errcolor++;
		i++;
	}
	if (i != 3)
		game->errcolor++;
}

void	line_check(char *line, t_game *game)
{
	int	i;
	int	nb;

	if (game->trim != NULL)
		free(game->trim);
	nb = 0;
	i = 1;
	while (line[i])
	{
		if (line[i] == ',')
		{
			if (line[i + 1] && line[i + 1] == ',')
				game->errcolor++;
			if (line[i + 1] && line[i + 1] == '\n')
				game->errcolor++;
			nb++;
		}
		i++;
	}
	if (nb != 2)
		game->errcolor++;
}

int	color_check(char **split, int *r, int *g, int *b)
{
	if (split[0])
		(*r) = ft_atoi(split[0]);
	if (split[0] && split[1])
		(*g) = ft_atoi(split[1]);
	if (split[0] && split[1] && split[2])
		(*b) = ft_atoi(split[2]);
	if ((*r) < 0 || (*r) > 255 || (*g) < 0
		|| (*g) > 255 || (*b) < 0 || (*b) > 255)
		return (1);
	return (0);
}
