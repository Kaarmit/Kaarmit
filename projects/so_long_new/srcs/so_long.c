/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 11:46:45 by aarmitan          #+#    #+#             */
/*   Updated: 2024/09/12 12:01:00 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

static int	is_ber_file(const char *av)
{
	char	*string;

	string = ft_strrchr(av, '.');
	if (string)
		return (ft_strcmp(string, ".ber") == 0);
	return (1);
}

int	main(int ac, char **av)
{
	t_game	game;

	if (ac == 2 && (is_ber_file(av[1])))
		init_game(&game, av[1]);
	else if (ac == 2 && !(is_ber_file(av[1])))
		end_game("Format not supported!", &game, file_error, NULL);
	else if (ac > 2)
		end_game("Can't open multiple files!", &game, file_error, NULL);
	else if (ac < 2)
		end_game("Missing .ber file!", &game, file_error, NULL);
	else
		end_game("Please specify file name!", &game, file_error, NULL);
	return (0);
}