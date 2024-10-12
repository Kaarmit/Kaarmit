/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_str.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 14:07:00 by aarmitan          #+#    #+#             */
/*   Updated: 2024/10/12 14:20:57 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int	main(int argc, char **argv)
{
	int	i = 0;
	int	first_word = 1;

	if (argc == 2)
	{
		while (argv[1][i])
		{
				while (argv[1][i] == ' ' || argv[1][i] == '\t')
					i++;
				if (argv[1][i] && !(argv[1][i] == ' ' || argv[1][i] == '\t'))
					if (!first_word)
						write(1, "   ", 3);
				while (argv[1][i] && !(argv[1][i] == ' ' || argv[1][i] == '\t'))
				{
					write(1, &argv[1][i], 1);
					i++;
				}
				first_word = 0;
		}
	}
	write(1, "\n", 1);
	return (0);
}

