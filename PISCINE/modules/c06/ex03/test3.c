/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 10:44:10 by aarmitan          #+#    #+#             */
/*   Updated: 2024/03/31 11:18:18 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int    ft_strcomp(char *str,char *strb)
{
	int    i;

	i = 0;
	while(str[i] && str[i] == strb[i])
	{
		i++;
	}
	return (str[i] - strb[i]);
}

int    ft_strlen(char *str)
{
	int    i;

	i = 0;
	while (str[i])
	{
		i++;
	}
	return (i);
}

void    rev_arg(char *str, int argc)
{
	int    i;
	char    temp;

	i = 0;

	while (str[i] && str[i] == str[i + 1])
	{    
		ft_strcomp(&str[i], &str[i + 1]);    
	}
	if (str[i] > str[i + 1])
	{
		temp = str[i];
		str[i] = str[i + 1];
		str[i + 1] = temp;
	}
	if (argc > 1)
		rev_arg(str, argc - 1);

}


int    main(int argc, char **argv)
{    
	int	i;

	i = 1;
	if (argc > 1)
	{
		rev_arg(*argv, argc - 1);
		write(1, &argv[i], ft_strlen(argv[argc]));
		argc--;
		i++;
	}
}
