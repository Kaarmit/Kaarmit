/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 14:37:42 by aarmitan          #+#    #+#             */
/*   Updated: 2024/11/21 15:15:02 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_args_number(char *arg)
{
	int	i;

	while (arg[i])
	{
		if (arg[i] < '0' && arg[i] > '9')
			return (1);
		i++;
	}
	return (0);
}

int	check_args_validty(char **argv)
{
	if (atoi(argv[1]) > PHILO_MAX || check_args_number(argv[1]) == 1)
		return (write(2, "Invalid philosophers number\n", 29), 1);
	if (ft_atoi(argv[2]) <= 0 || check_arg_content(argv[2]) == 1)
		return (write(2, "Invalid time to die\n", 21), 1);
	if (ft_atoi(argv[3]) <= 0 || check_arg_content(argv[3]) == 1)
		return (write(2, "Invalid time to eat\n", 21), 1);
	if (ft_atoi(argv[4]) <= 0 || check_arg_content(argv[4]) == 1)
		return (write(2, "Invalid time to sleep\n", 23), 1);
	if (argv[5] && (ft_atoi(argv[5]) < 0 || check_arg_content(argv[5]) == 1))
		return (write(2, "Invalid number of times each philosopher must eat\n",
				51), 1);
	return (0);
}

int	main(int argc, char **argv)
{
	if (argc < 4 || argc > 5)
		return (write(2, "Wrong number of arguments\n", 26), 1);
	if (check_args_validty(argv) == 1)
		return (1);
	init_program;
	init_forks;
	init_philos;
	thread_create;
	destroy_all;
}
