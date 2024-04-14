/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 13:29:37 by aarmitan          #+#    #+#             */
/*   Updated: 2024/04/04 14:18:38 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
int	scan(char *str, char c, int nb)
{
	while (nb >= 0)
	{
		if (str[nb] == c)
			return (0);
		nb --;
	}
	return (1);
}
void	inter(char *s1, char *s2)
{
	int	i = 0;
	int	j = 0;

	while(s1[i])
	{
		while(s2[j])
		{
			if(s1[i] == s2[j])
			{
				if (scan(s1, s1[i], i - 1))
					write(1, &s1[i], 1);
				break;
			}
			j++;
		}
		i++;
	}
}

int	main(int argc, char **argv)
{
	if (argc == 3)
		inter(argv[1], argv[2]);
	write(1, "\n", 1);
}

