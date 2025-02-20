/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-hadr <oel-hadr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 19:06:40 by oel-hadr          #+#    #+#             */
/*   Updated: 2025/02/20 17:48:46 by oel-hadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philosopher_routine(void *arg)
{
	t_philo *philo = (t_philo *)arg;
	t_philo_args *args = philo->args;
	int			running;

	if (philo->args->number_of_philosophers == 1)
	{
		pthread_mutex_lock(&philo->left_fork->mutex);
		print_status(philo, "has taken a fork");
		long start_time = get_time();
		while ((get_time() - start_time) < philo->args->time_to_die)
			usleep(500);
		print_status(philo, "died");
		pthread_mutex_unlock(&philo->left_fork->mutex);
		args->simulation_running = 0;
		return (NULL);
	}

	pthread_mutex_lock(&philo->args->sim_mutex);
	running = philo->args->simulation_running;
	pthread_mutex_unlock(&philo->args->sim_mutex);
	while (running)
	{
		eat(philo);
		print_status(philo, "is sleeping");
		usleep(philo->args->time_to_sleep * 1000);
		print_status(philo, "is thinking");
		pthread_mutex_lock(&philo->args->sim_mutex);
		running = philo->args->simulation_running;
		pthread_mutex_unlock(&philo->args->sim_mutex);
	}
	return NULL;
}

void	*monitor_routine(void *arg)
{
	int	i;
	int	full_philos_count;
	
	t_philo_args *args = (t_philo_args *)arg;
	while (args->simulation_running)
	{
		i = 0;
		full_philos_count = 0;
		while (i < args->number_of_philosophers)
		{
			if (args->min_must_eat > 0 && args->philos[i].meals_eaten >= args->min_must_eat)
				full_philos_count++;
			pthread_mutex_lock(&args->meal_mutex);
			long last_meal = args->philos[i].last_meal_time;
			pthread_mutex_unlock(&args->meal_mutex);
			if (get_time() - last_meal >= args->time_to_die)
			{
				print_status(&args->philos[i], "died");
				pthread_mutex_lock(&args->sim_mutex);
				args->simulation_running = 0;
				pthread_mutex_unlock(&args->sim_mutex);
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
	}
	return NULL;
}
