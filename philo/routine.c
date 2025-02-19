/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-hadr <oel-hadr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 19:06:40 by oel-hadr          #+#    #+#             */
/*   Updated: 2025/02/19 20:26:39 by oel-hadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philosopher_routine(void *arg)
{
	t_philo *philo = (t_philo *)arg;
	t_philo_args *args = philo->args;

	if (philo->id % 2 == 0)
		usleep(1000);

	while (args->simulation_running)
	{
		think(philo);
		eat(philo);
		sleep_philo(philo);
		if (args->min_must_eat > 0 && philo->meals_eaten >= args->min_must_eat)
			break ;
	}
	return NULL;
}

void	*monitor_routine(void *arg)
{
	int	i;
	int	full_philos_count;
	
	t_philo_args *args = (t_philo_args *)arg;
	
	while (1)
	{
		i = 0;
		full_philos_count = 0;
		while (i < args->number_of_philosophers)
		{
			pthread_mutex_lock(&args->print_mutex);
			if (args->min_must_eat > 0 && args->philos[i].meals_eaten >= args->min_must_eat)
				full_philos_count++;

			if (get_time() - args->philos[i].last_meal_time > args->time_to_die)
			{
				print_status(&args->philos[i], "died");
				args->simulation_running = 0;
				pthread_mutex_unlock(&args->print_mutex);
				return NULL;
			}
			pthread_mutex_unlock(&args->print_mutex);
			i++;
		}
		if (full_philos_count == args->number_of_philosophers)
		{
			args->simulation_running = 0;
			return NULL;
		}
		usleep(1000);
	}
	return NULL;
}
