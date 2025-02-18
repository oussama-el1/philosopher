/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-hadr <oel-hadr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 15:54:09 by oel-hadr          #+#    #+#             */
/*   Updated: 2025/02/18 18:23:04 by oel-hadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H

#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <pthread.h>

typedef struct	s_philo_args
{
	int	number_of_philosophers;
	int	number_forks;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	min_must_eat;
}		t_philo_args;

typedef struct s_fork
{
	pthread_mutex_t mutex;
}   t_fork;

typedef struct s_philo
{
	int			id;
	pthread_t	thread;
	int			meals_eaten;
	long long	last_meal_time;
	t_fork		*left_fork;
	t_fork		*right_fork;
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
	t_philo			*philos;
	t_fork			*forks;
	pthread_mutex_t	print_mutex;
}   t_philo_args;


// helpers
int	ft_atoi(const char *str);
int	is_valid_number(const char *str);

// philos functions
int	init_philos(t_philo_args *args);

#endif
