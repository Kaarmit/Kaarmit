/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wdmatch.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 09:21:33 by aarmitan          #+#    #+#             */
/*   Updated: 2024/04/04 11:46:28 by aarmitan         ###   ########.fr       */
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

void	wdmatch(char *s1, char *s2)
{
	int	i = 0;
	int	j = 0;

	while (s1[i] && s2[j])
	{
		if (s2[j] == s1[i])
			i++;
		j++;
	}
	if (i == ft_strlen(s1))
		write(1, s1, i);		
}		
int	main(int argc, char **argv)
{
	if (argc == 3)
		wdmatch(argv[1], argv[2]);
	write(1, "\n", 1);
	return (0);
}
