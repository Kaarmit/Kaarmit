/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abastian <abastian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 15:44:01 by abastian          #+#    #+#             */
/*   Updated: 2025/07/11 19:13:21 by abastian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	path_check(t_game *game)
{
	int	flag;

	flag = 0;
	if (game->nopath == NULL)
		flag++;
	if (game->sopath == NULL)
		flag++;
	if (game->wepath == NULL)
		flag++;
	if (game->eapath == NULL)
		flag++;
	// if (game->fcolor == -1)
	// 	flag++;
	// if (game->ccolor == -1)
	// 	flag++;
	if (flag != 0)
		return (1);
	return (0);
}

void	get_color(char *line, int *color, t_game *game, int i)
{
	int		r;
	int		g;
	int		b;
	char	**split;

	r = -1;
	g = -1;
	b = -1;
	line_check(line, game);
	game->trim = ft_strtrim(&line[1], " \n\t");
	if (*color != -1)
	{
		game->doublepath++;
		return ;
	}
	while (game->trim[i] == ' ')
		i++;
	split = ft_split(&game->trim[i], ',');
	if (!split || !split[0] || !split[1] || !split[2])
		game->errcolor++;
	split_check(split, game);
	if (color_check(split, &r, &g, &b) != 0)
		game->errcolor++;
	*color = (r << 16) | (g << 8) | b;
	freegrid(split);
}

void	get_path(char *line, char **path, t_game *game)
{
	int	i;

	i = 2;
	if ((*path) != NULL)
	{
		game->doublepath++;
		return ;
	}
	while (line[i] == ' ')
		i++;
	if (line[i] == '\n')
		(*path) = NULL;
	else
	{
		(*path) = ft_strtrim(&line[i], "\n\t");
		if (!(*path))
			(*path) = NULL;
		if ((*path) && !name_check_texture((*path)))
			game->doublepath++;
	}
}

char	*get_info(char *line, t_game *game, int fd)
{
	while (line)
	{
		if (line == NULL)
			break ;
		if (ft_strncmp(line, "NO ", 3) == 0)
			get_path(line, &game->nopath, game);
		else if (ft_strncmp(line, "SO ", 3) == 0)
			get_path(line, &game->sopath, game);
		else if (ft_strncmp(line, "WE ", 3) == 0)
			get_path(line, &game->wepath, game);
		else if (ft_strncmp(line, "EA ", 3) == 0)
			get_path(line, &game->eapath, game);
		else if (ft_strncmp(line, "F ", 2) == 0)
			get_color(line, &game->fcolor, game, 1);
		else if (ft_strncmp(line, "C ", 2) == 0)
			get_color(line, &game->ccolor, game, 1);
		else if (ft_strncmp(line, "\n", 1) != 0)
			return (line);
		free(line);
		line = get_next_line(fd);
	}
	return (NULL);
}

char	*get_map(char *map, t_game *game, char *temp)
{
	int		fd;
	char	*line;
	char	*bigline;

	fd = open(map, O_RDONLY);
	if (fd < 0)
		error_game("Could not open the map.", game);
	line = get_next_line(fd);
	if (!line)
		return (close(fd), error_game("Given map is empty !", game), NULL);
	line = get_info(line, game, fd);
	bigline = ft_strdup("");
	if (!bigline)
		return (close(fd), free(bigline), error_game("strdup", game), NULL);
	while (line)
	{
		if (line == NULL)
			break ;
		temp = ft_strjoin(bigline, line);
		free(bigline);
		bigline = temp;
		free(line);
		line = get_next_line(fd);
	}
	return (close(fd), bigline);
}
