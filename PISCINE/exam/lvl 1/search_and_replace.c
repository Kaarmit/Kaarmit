/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_and_replace.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 14:53:35 by aarmitan          #+#    #+#             */
/*   Updated: 2024/03/30 15:59:36 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int	main(int argc, char **argv)
{
	int	i;

	i = 0;
	if (argc == 4)
	{
		while (argv[1][i])
		{
			if (!argv[2][1] && !argv[3][1])
			{
				if (argv[1][i] == argv[2][0])
				{
					write(1, &argv[3][0], 1);
				}
				else 
				{
					write(1, &argv[1][i], 1);
				}
				i++;
			}
		}
	}
}




/*
void ft_swap(char *a, char *b)
{
	char temp;
	temp = *a;
	*a = *b;
	*b = temp;
}

int main(int argc, char **argv)
{
	int i = 0;

	if (argc == 4)
	{
		if (!argv[2][1] && !argv[3][1])
		{
			while (argv[1][i] != '\0')
			{
				if (argv[1][i] == argv[2][0]) 
				{
					ft_swap(&argv[1][i], &argv[3][0]);
				}
				i++; 
			}
			write(1, &argv[1], i); 
		}
	}
	write(1, "\n", 1);
	return 0;
}
*/
