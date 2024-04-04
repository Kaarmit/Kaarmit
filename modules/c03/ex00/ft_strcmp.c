/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 10:56:42 by aarmitan          #+#    #+#             */
/*   Updated: 2024/03/28 10:36:08 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_strcmp(char *s1, char *s2)
{
	unsigned int	i;

	i = 0;
	while (s1[i] != '\0' && s2[i] != '\0' && s1[i] == s2[i])
	{
		i++;
	}
	return (s1[i] - s2[i]);
}


#include <stdio.h>
#include <string.h>

int	main(void)
{
	char	s1[] = "a";
	char	s2[] = "as";
	printf("%d, %d\n", ft_strcmp(s1, s2), strcmp(s1, s2));
}

