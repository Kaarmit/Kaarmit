/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_params_test.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 19:23:02 by aarmitan          #+#    #+#             */
/*   Updated: 2024/03/30 23:00:12 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int	ft_strcomp(char *s1,char *s2)
{
	while(*s1 && *s1 == *s2)
	{
		s1++;
		s2++;	
	}
	return (s1 - s2);
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		i++;
	}
	return (i);
}

void	ft_swap(char *s1, char *s2)
{
	char	temp;

	temp = *s1;
	*s1 = *s2;
	*s2 = temp;
}


void	rev_arg(char *s1, char *s2) 
{
	int	i;
	int	j;

	i = 0;
	j = 0;

	while (*s1 && *s2)
	{	
		ft_strcomp(s1, s2); 	
	}
	if (*s1 > *s2)
	{
		ft_swap(s1, s2);
	}
}


int	main(int argc, char **argv)
{	
	int	i;

	i = 1;
	while (argc > 1)
	{
		rev_arg(argv[i], argv[i + 1]);
		write(1, &argv[i], ft_strlen(&argv[i][argc])); 
		i++;
	}
}
