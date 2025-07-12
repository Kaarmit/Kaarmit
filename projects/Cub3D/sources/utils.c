/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 12:52:27 by abastian          #+#    #+#             */
/*   Updated: 2025/07/11 14:25:13 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	freegrid(char **grid)
{
	int	i;

	i = 0;
	while (grid[i])
	{
		free(grid[i]);
		i++;
	}
	free(grid);
	grid = NULL;
}

void	game_over(t_game *game, int danger)
{
	if (danger == 1)
		printf("\nAn enemy caught you ! Loser !\n");
	destroy_all(game);
	exit(EXIT_SUCCESS);
}

int	name_check_texture(char *name)
{
	int	i;

	i = 0;
	while (name[i])
		i++;
	i--;
	if (name[i] == 'm')
		i--;
	else
		return (0);
	if (name[i] == 'p')
		i--;
	else
		return (0);
	if (name[i] == 'x')
		i--;
	else
		return (0);
	if (name[i] == '.' && name[i - 1] != '\0')
		return (1);
	return (0);
}

int	name_check(char *name)
{
	int	i;

	i = 0;
	while (name[i])
		i++;
	i--;
	if (name[i] == 'b')
		i--;
	else
		return (0);
	if (name[i] == 'u')
		i--;
	else
		return (0);
	if (name[i] == 'c')
		i--;
	else
		return (0);
	if (name[i] == '.' && name[i - 1] != '\0')
		return (1);
	return (0);
}

int	each_line_check(char *getmap)
{
	int	i;

	i = 0;
	if (getmap[0] == '\n')
		return (1);
	while (getmap[i])
	{
		if (getmap[i] == '\n' && getmap[i + 1] == '\n')
			return (1);
		i++;
	}
	return (0);
}
