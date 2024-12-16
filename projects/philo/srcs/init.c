/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 16:18:59 by aarmitan          #+#    #+#             */
/*   Updated: 2024/12/16 12:47:57 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	init_args(t_philo *philo, char **argv)
{
	philo->nbr_of_philos = ft_atoi(argv[1]);
	philo->time_to_die = ft_atoi(argv[2]);
	philo->time_to_eat = ft_atoi(argv[3]);
	philo->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		philo->nbr_of_times_to_eat = ft_atoi(argv[5]);
	else
		philo->nbr_of_times_to_eat = -1;
}

void	init_philos(t_philo *philos, t_program *program, pthread_mutex_t *forks,
		char **argv)
{
	int	i;

	i = 0;
	while (i < ft_atoi(argv[1]))
	{
		philos[i].id = i + 1;
		philos[i].eating = 0;
		philos[i].meals_eaten = 0;
		init_args(&philos[i], argv);
		philos[i].start_time = get_current_time();
		philos[i].last_meal = get_current_time();
		philos[i].write_lock = &program->write_lock;
		philos[i].dead_lock = &program->dead_lock;
		philos[i].meal_lock = &program->meal_lock;
		philos[i].dead = &program->dead_flag;
		philos[i].l_fork = &forks[i];
		if (i == 0)
			philos[i].r_fork = &forks[philos[i].nbr_of_philos - 1];
		else
			philos[i].r_fork = &forks[i - 1];
		i++;
	}
}

void	init_forks(pthread_mutex_t *forks, int philo_num)
{
	int	i;

	i = 0;
	while (i < philo_num)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
}

void	init_program(t_program *program, t_philo *philos)
{
	program->dead_flag = 0;
	program->philos = philos;
	pthread_mutex_init(&program->write_lock, NULL);
	pthread_mutex_init(&program->dead_lock, NULL);
	pthread_mutex_init(&program->meal_lock, NULL);
}

// void	print_philo(int num, t_program *program)
// {
// 	int	i;

// 	i = 0;
// 	while (i < num)
// 	{
// 		printf("PHILO ATTENDU NUMERO %d :\n\n", i + 1);
// 		printf("ID PHILO : %d\n", program->philos[i].id);
// 		printf("TIME TO DIE : %zu\n", program->philos[i].time_to_die);
// 		printf("TIME TO EAT : %zu\n", program->philos[i].time_to_eat);
// 		printf("TIME TO SLEEP : %zu\n", program->philos[i].time_to_sleep);
// 		printf("NUM OF MEALS : %d\n", program->philos[i].nbr_of_times_to_eat);
// 		printf("START_TIME : %zu\n", program->philos[i].start_time);
// 		printf("LAST_MEAL : %zu\n", program->philos[i].last_meal);
// 		printf("L_FORK : %p\n", (void *)program->philos[i].l_fork);
// 		printf("R_FORK : %p\n", (void *)program->philos[i].r_fork);
// 		printf("WRITE_LOCK : %p\n", (void *)program->philos[i].write_lock);
// 		printf("MEAL_LOCK : %p\n", (void *)program->philos[i].meal_lock);
// 		printf("DEAD_LOCK : %p\n\n", (void *)program->philos[i].dead_lock);
// 		i++;
// 	}
// }
