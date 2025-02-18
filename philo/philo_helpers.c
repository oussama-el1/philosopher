/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-hadr <oel-hadr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 18:04:44 by oel-hadr          #+#    #+#             */
/*   Updated: 2025/02/18 18:25:16 by oel-hadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


int	init_philos(t_philo_args *args)
{
	int	i;

	args->philos = (t_philo *)malloc(sizeof(t_philo) * args->number_of_philosophers);
	if (!args->philos)
		return (-1);
	args->forks = (t_fork *)malloc(sizeof(t_fork) * args->number_forks);
	if (!args->forks)
	{
		free(args->philos);
		return (-1);
	}
	i = 0;
	while (i < args->number_of_philosophers)
	{
		args->philos[i].id = i;
		args->philos->meals_eaten = 0;
		args->philos->last_meal_time = 0;
		args->philos->left_fork	= &args->forks[i];
		args->philos->right_fork = &args->forks[(i + 1) & args->number_of_philosophers];
		pthread_mutex_init(&args->forks[i], NULL);
		i++;
	}
	pthread_mutex_init(&args->print_mutex, NULL);
}
