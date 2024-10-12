/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_prime_sum.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 18:24:46 by aarmitan          #+#    #+#             */
/*   Updated: 2024/10/09 18:31:09 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int	ft_atoi(char *s)
{
	int	res;

	res = 0;
	while (*s)
		res = res * 10 + *s++ - 48;
	return (res);
}

int	is_prime(int num)
{
	int	i;

	i = 2;
	if (num <= 1)
		return (0);
	while (i * i <= num)
	{
		if (num % i == 0)
			return (0);
		i++;
	}
	return (1);
}

void	put_nbr(int n)
{
	char	digit;

	if (n >= 10)
		put_nbr(n / 10);
	digit = n % 10 + '0';
	write(1, &digit, 1);
}

int	main(int argc, char **argv)
{
	int	nbr;
	int	sum;

	if (argc == 2)
	{
		nbr = ft_atoi(argv[[1]]);
		sum = 0;
		while (nbr > 0)
		{
			if (is_prime(nbr))
				sum += nbr;
			nbr--;
		}
		put_nbr(sum);
	}
	if (ac != 2)
		put_nbr(0);
	write(1, "\n", 1);
	return (0);
}
