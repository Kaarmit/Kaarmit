/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   union.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 11:48:36 by aarmitan          #+#    #+#             */
/*   Updated: 2024/04/04 12:18:12 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int	not_seen(char *str, int max_pos, char c)
{
	int	i = 0;

	while (i < max_pos)
	{
		if(str[i] == c)
			return(0);
		i++;
	}
	return (1);
}

void	ft_union(char *s1, char *s2)
{
	int	i = 0;
	int	j = 0;

	while (s1[i])
	{
		if (not_seen(s1, i, s1[i]))
			write(1, &s1[i], 1);
		i++;
	}
	while (s2[j])
	{
		if  ((not_seen(s1, i, s2[j])) && (not_seen(s2, j, s2[j])))
			write(1, &s2[j], 1);
		j++;
	}
}

int	main(int argc, char **argv)
{
	if (argc == 3)
		ft_union(argv[1], argv[2]);
	write(1, "\n", 1);
	return (0);
}

