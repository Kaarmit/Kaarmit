/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_params.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 17:17:35 by aarmitan          #+#    #+#             */
/*   Updated: 2024/03/30 19:20:00 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

/*
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
*/
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

void	rev_arg(int argc, char **argv)
{
	int	i;
	int	j;
	char	temp;

	i = 1;
	j = argc - 1;

	while (i < j)
	{
		temp = *argv[i];
		*argv[i] = *argv[j];
		*argv[j] = temp;
	}
	
}


int	main(int argc, char **argv)
{	
	int	i;

	i = 1;
	while (i > argc)
	{
		rev_arg(argv[i], argv[argc - 1]);
		write(1, &argv[i], ft_strlen(argv[argc]));
		argc--;
		i++;
	}
}
