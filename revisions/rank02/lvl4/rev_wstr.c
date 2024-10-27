/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rev_wstr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 17:29:03 by aarmitan          #+#    #+#             */
/*   Updated: 2024/10/15 09:06:19 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int	main(int argc, char **argv)
{
	int	start;
	int	end;
	int	i;
	int	flag;

	i = 0;
	if (argc == 2)
	{
		while (argv[1][i] != '\0')
			i++;
		while (i >= 0)
		{
			while (argv[1][i] == '\0' || argv[1 [i]] == ' ' || argv[1][i] == '\t')
				i--;
			end = i;
			while (argv[1][i] && argv[1][i] != ' ' && rgv[1][i] != '\t')
				i--;
			start = i + 1;
			flag = start;
			while (start <= end)
			{
				write(1, &argv[1][start], 1);
				start++;
			}
			if (flag != 0)
				write(1, " ", 1);
		}
	}
	write(1, "\n", 1);
}
