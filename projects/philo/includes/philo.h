/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 14:16:41 by aarmitan          #+#    #+#             */
/*   Updated: 2024/11/26 16:56:11 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

# define PHILO_MAX 200

typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	int				eating;
	int				meals_eaten;
	size_t			last_meal;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	size_t			start_time;
	int				nbr_of_philos;
	int				nbr_of_times_to_eat;
	int				*dead;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*write_lock;
	pthread_mutex_t	*dead_lock;
	pthread_mutex_t	*meal_lock;
}					t_philo;

typedef struct s_program
{
	int				dead_flag;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	write_lock;
	t_philo			*philos;
}					t_program;

void				init_args(t_philo *philo, char **argv);
void				init_philos(t_philo *philos, t_program *program,
						pthread_mutex_t *forks, char **argv);
void				init_forks(pthread_mutex_t *forks, int philo_num);
void				init_program(t_program *program, t_philo *philos);
void				print_philo(int num, t_program *program);
int					check_args_number(char *arg);
int					check_args_validty(char **argv);
int					main(int argc, char **argv);
int					ft_atoi(char *str);
int					ft_strlen(char *str);
size_t				get_current_time(void);
int					ft_usleep(size_t milliseconds);
void				destory_all(char *str, t_program *program,
						pthread_mutex_t *forks);
void				*monitor(void *arg);
void				think(t_philo *philo);
void				dream(t_philo *philo);
void				eat(t_philo *philo);
int					thread_create(t_program *program, pthread_mutex_t *forks);
void				*philo_routine(void *pointer);
int					dead_loop(t_philo *philo);
void				print_message(char *str, t_philo *philo, int id);
void				*monitor(void *arg);

#endif
