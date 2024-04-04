/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 19:23:02 by aarmitan          #+#    #+#             */
/*   Updated: 2024/03/30 22:46:03 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int	ft_strcomp(char *str,char *strb)
{
	int	i;

	i = 0;
	while(str[i] && str[i] == strb[i])
	{
		i++;
	}
	return (str[i] - strb[i]);
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

int	main(int argc, char **argv)
{	

	int	i;
	int	j;
	char	temp;

	i = 0;
	j = 0;

	while (argv[i] && argv[j])
	{	
		ft_strcomp(&argv[i], &argv[j]); 	
		i++;
		j++;
	}
	if (argv[i] > argv[j])
	{
		temp = *str;
		*str = *strb;
		*strb = temp;
	}
	
	while (argc > 1)
	{
	}
	write(1, &argv[argc], ft_strlen(argv[argc])); 
}
