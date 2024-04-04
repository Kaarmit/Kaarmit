/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_is_printable.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 16:23:27 by aarmitan          #+#    #+#             */
/*   Updated: 2024/03/24 09:52:40 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_str_is_printable(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] >= 32 && str[i] <= 126)
			i++;
		else
			return (0);
	}
	return (1);
}

/*
#include <unistd.h>
int	main(void)
{
	char	*str = "";
	
	int	p;
	p = ft_str_is_printable(str);
	if (p == 1)
	{
		write(1, "yes", 3);
	}
	else
	{
		write(1, "no", 2);
	}
}
*/	
