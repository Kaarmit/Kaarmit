/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   union.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 11:55:59 by aarmitan          #+#    #+#             */
/*   Updated: 2024/04/02 12:30:55 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int	ft_strlen(char *str)
{
	int	i = 0;

	while (str[i])
		i++;
	return (i);
}

int	main(int argc, char **argv)
{
	int	i = 0;
	int	j = 0;
	char	*str = 0;

	while (argc == 3)
	{
		while (argv[1][i])
		{
			while (argv[1][i] != str[j] && str[j])
				j++;
			if (argv[1][i] == str[j])
				i++;
			else if (str[j] == '\0')
			{
				str[j] = argv[1][i];
				i++;
			}
			//str[j] = argv[1][i];
		//	else if (argv[1][i] == str[j++]
		}	
	}
	write(1, &str, ft_strlen(str));
}	










//while (str[i] && argv[1][i] && str[i] != argv[1][i])
//		{
//			str[i] = argv[1][i]
//			i++;
		
		
