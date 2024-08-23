/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 13:59:18 by aarmitan          #+#    #+#             */
/*   Updated: 2024/08/23 17:42:12 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

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


