/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-hadr <oel-hadr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 15:54:09 by oel-hadr          #+#    #+#             */
/*   Updated: 2025/02/19 19:44:26 by oel-hadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H

#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <pthread.h>
#include <sys/time.h>
#include <unistd.h>

typedef struct s_fork
{
	pthread_mutex_t mutex;
}   t_fork;

struct s_philo_args;

typedef struct s_philo
{
	int			id;
	pthread_t	thread;
	int			meals_eaten;
	long long	last_meal_time;
	t_fork		*left_fork;
	t_fork		*right_fork;
	struct s_philo_args *args;
}	t_philo;

typedef struct s_philo_args
{
	int				number_of_philosophers;
	int				number_forks;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				min_must_eat;
	long long		start_time;
	int				simulation_running;
	t_philo			*philos;
	t_fork			*forks;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	sim_mutex;
}   t_philo_args;


// helpers
int			ft_atoi(const char *str);
int			is_valid_number(const char *str);
void		print_status(t_philo *philo, char *status);
long long	get_time(void);
void		pick_up_forks(t_philo *philo);
void		put_down_forks(t_philo *philo);
void		cleanup(t_philo_args *args);

// init function
int	init_philos(t_philo_args *args);
void	init_threads(t_philo_args *args);

// routine
void	*philosopher_routine(void *arg);
void	*monitor_routine(void *arg);
void	think(t_philo *philo);
void	eat(t_philo *philo);
void	sleep_philo(t_philo *philo);

#endif
