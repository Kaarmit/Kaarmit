/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 11:46:32 by aarmitan          #+#    #+#             */
/*   Updated: 2024/10/14 15:34:16 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	join_me(char **lines, char **curr, t_game *game)
{
	char	*tmp;

	tmp = *lines;
	*lines = ft_strjoin(*lines, *curr);
	free(tmp);
	free(*curr);
	if (!(*lines))
		end_game(ERRSAVE, game, file_error, NULL);
}

void	pass_empty_lines(char **lines, int *fd, t_game *game, int *err)
{
	*lines = get_next_line(*fd, err);
	if (!(*lines))
		end_game(ERRFILE1, game, file_error, NULL);
	while (*lines && *lines[0] == '\n')
	{
		free(*lines);
		*lines = get_next_line(*fd, err);
	}
	return ;
}

char	**get_map(char *map_file, t_game *game, int err)
{
	char	*curr;
	char	*lines;
	int		fd;

	fd = open(map_file, O_RDONLY);
	if (fd < 0)
		end_game(ERROPEN, game, file_error, NULL);
	pass_empty_lines(&lines, &fd, game, &err);
	curr = get_next_line(fd, &err);
	if (!curr)
		free(lines);
	while (curr)
	{
		if (curr[0] == '\n')
		{
			free(curr);
			break ;
		}
		join_me(&lines, &curr, game);
		curr = get_next_line(fd, &err);
		if (err == 1)
			end_game(ERRSAVE, game, file_error, NULL);
	}
	close (fd);
	return (ft_split(lines, '\n'));
}
