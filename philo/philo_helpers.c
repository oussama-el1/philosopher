/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-hadr <oel-hadr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 18:04:44 by oel-hadr          #+#    #+#             */
/*   Updated: 2025/03/18 10:33:24 by oel-hadr         ###   ########.fr       */
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
	pthread_mutex_init(&args->forks[i].mutex, NULL);
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
	while (i < args->number_of_philosophers)
	{
		init_philo(args, i);
		i++;
	}
	pthread_mutex_init(&args->print_mutex, NULL);
	pthread_mutex_init(&args->meal_mutex, NULL);
	pthread_mutex_init(&args->dead_mutex, NULL);
	return (0);
}

void	init_threads(t_philo_args *args)
{
	int			i;
	pthread_t	monitor;

	i = -1;
	while (++i < args->number_of_philosophers)
	{
		args->philos[i].born_at = get_time();
		if (pthread_create(&args->philos[i].thread, NULL,
				philosopher_routine, &args->philos[i]) != 0)
		{
			cleanup(args, "Error: creating thread\n");
			return ;
		}
	}
	if (pthread_create(&monitor, NULL, monitor_routine, args) != 0)
	{
		cleanup(args, "Error: creating Monitor\n");
		return ;
	}
	i = -1;
	while (++i < args->number_of_philosophers)
		pthread_join(args->philos[i].thread, NULL);
	pthread_join(monitor, NULL);
}
