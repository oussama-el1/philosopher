/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-hadr <oel-hadr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 18:04:44 by oel-hadr          #+#    #+#             */
/*   Updated: 2025/04/17 15:33:16 by oel-hadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	init_philo(t_philo_args *args, int i)
{
	args->philos[i].id = i + 1;
	args->philos[i].meals_eaten = 0;
	args->philos[i].last_meal_time = get_time();
	args->philos[i].left_fork = &args->forks[i];
	args->philos[i].right_fork = &args->forks[(i + 1)
		% args->number_of_philosophers];
	args->philos[i].args = args;
	if (pthread_mutex_init(&args->forks[i].mutex, NULL) != 0)
	{
		cleanup(args, "Error: creating fork mutex\n", 0, i + 1);
		return ;
	}
}

void	init_mutex(t_philo_args *args)
{
	if (pthread_mutex_init(&args->print_mutex, NULL) != 0)
	{
		cleanup(args, "Error: creating print mutex\n", 0, args->number_forks);
		return ;
	}
	if (pthread_mutex_init(&args->meal_mutex, NULL) != 0)
	{
		cleanup(args, "Error: creating meal mutex\n", 0, args->number_forks);
		pthread_mutex_destroy(&args->print_mutex);
		return ;
	}
	if (pthread_mutex_init(&args->dead_mutex, NULL) != 0)
	{
		cleanup(args, "Error: creating dead mutex\n", 0, args->number_forks);
		pthread_mutex_destroy(&args->print_mutex);
		pthread_mutex_destroy(&args->meal_mutex);
		return ;
	}
}

int	init_philos(t_philo_args *args)
{
	int	i;

	args->philos = malloc(sizeof(t_philo) * args->number_of_philosophers);
	if (!args->philos)
		return (-1);
	args->forks = malloc(sizeof(t_fork) * args->number_of_philosophers);
	if (!args->forks)
	{
		free(args->philos);
		return (-1);
	}
	i = 0;
	args->start_time = get_time();
	while (i < args->number_of_philosophers)
	{
		init_philo(args, i);
		i++;
	}
	init_mutex(args);
	return (0);
}

void	clean_threads(t_philo_args *args, int num)
{
	int	i;

	i = 0;
	while (i < num)
	{
		pthread_join(args->philos[i].thread, NULL);
		i++;
	}
	cleanup(args, "Error: creating thread\n", 1, args->number_forks);
}

void	init_threads(t_philo_args *args)
{
	int			i;
	pthread_t	monitor;

	i = -1;
	while (++i < args->number_of_philosophers)
	{
		if (pthread_create(&args->philos[i].thread, NULL,
				philosopher_routine, &args->philos[i]) != 0)
		{
			clean_threads(args, i);
			return ;
		}
	}
	if (pthread_create(&monitor, NULL, monitor_routine, args) != 0)
	{
		clean_threads(args, args->number_of_philosophers);
		return ;
	}
	i = -1;
	while (++i < args->number_of_philosophers)
		pthread_join(args->philos[i].thread, NULL);
	pthread_join(monitor, NULL);
}
