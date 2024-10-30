/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaabdall <yaabdall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 18:58:51 by yaabdall          #+#    #+#             */
/*   Updated: 2024/09/17 20:25:47 by yaabdall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
The atoi libc function stands for "ASCII to integer" and
is used to convert a string (*str) into an integer (sign * nbr).
*/
#include "../../includes/libft.h"
#include "../../includes/ft_printf.h"

static int	ft_isspace(char c)
{
	return ((c >= '\t' && c <= '\r') || c == ' ');
}

int	ft_atoi(const char *str, int *error)
{
	size_t	i;
	int		sign;
	long	nbr;

	i = 0;
	sign = 1;
	nbr = 0;
	*error = 0;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	i--;
	while (ft_isdigit(str[++i]))
		nbr = nbr * 10 + str[i] - '0';
	if (nbr * sign > INT_MAX || nbr * sign < INT_MIN)
		*error = 1;
	return (nbr * sign);
}
/*
#include <stdio.h>
#include <string.h>

int	main(int argc, char **argv)
{
	if (argc > 1)
	{
		printf("atoi: %d\n", atoi(argv[1]));
		printf("ft_atoi: %d\n", ft_atoi(argv[1]));
	}
	return (0);
}
*/
