/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 10:05:13 by aarmitan          #+#    #+#             */
/*   Updated: 2024/10/30 16:04:31 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

static int	ft_check_int(char *value)
{
	int	error;
	int	i;

	if ((value[0] == '+' || value[0] == '-' ) && !ft_isdigit(value[1]))
		return (0);
	i = 0;
	if (value[0] == '+' || value[0] == '-' )
		i++;
	while (value[i])
	{
		if (!ft_isdigit(value[i]))
			return (0);
		i++;
	}
	ft_atoi(value, &error);
	if (error)
		return (0);
	return (1);
}

static int	ft_check_duplicates(char **argv)
{
	int	i;
	int	j;
	int	error;

	i = 0;
	while (argv[++i])
	{
		j = i;
		while (argv[++j])
		{
			if (i != j && ft_atoi(argv[i], &error) == ft_atoi(argv[j], &error))
				return (1);
		}
	}
	return (0);
}

int	check_data(char **argv)
{
	int	i;

	if (!argv || !argv[1] || !*argv[1])
		return (0);
	i = 0;
	while (argv[++i])
	{
		if (!ft_check_int(argv[i]))
			return (0);
	}
	if (ft_check_duplicates(argv))
		return (0);
	return (1);
}
