/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_helpers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-hadr <oel-hadr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 19:10:04 by oel-hadr          #+#    #+#             */
/*   Updated: 2025/04/17 15:02:58 by oel-hadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eat(t_philo *philo)
{
	pick_up_forks(philo);
	pthread_mutex_lock(&philo->args->meal_mutex);
	philo->last_meal_time = get_time();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->args->meal_mutex);
	print_status(philo, EAT);
	ft_usleep(philo->args->time_to_eat);
	put_down_forks(philo);
}

void	set_running_status(int *running, t_philo *philo)
{
	pthread_mutex_lock(&philo->args->dead_mutex);
	*running = philo->args->simulation_running;
	pthread_mutex_unlock(&philo->args->dead_mutex);
}

int	is_all_full(t_philo_args *args)
{
	int	i;

	i = 0;
	while (i < args->number_of_philosophers)
	{
		pthread_mutex_lock(&args->meal_mutex);
		if (args->min_must_eat < 0
			|| args->philos[i].meals_eaten < args->min_must_eat)
		{
			pthread_mutex_unlock(&args->meal_mutex);
			return (0);
		}
		pthread_mutex_unlock(&args->meal_mutex);
		i++;
	}
	pthread_mutex_lock(&args->dead_mutex);
	args->simulation_running = 0;
	pthread_mutex_unlock(&args->dead_mutex);
	return (1);
}

int	is_dead(t_philo_args *args, t_philo *philo)
{
	int	dead;

	pthread_mutex_lock(&args->meal_mutex);
	dead = (get_time() - philo->last_meal_time > args->time_to_die);
	pthread_mutex_unlock(&args->meal_mutex);
	return (dead);
}

int	is_all_alive(t_philo_args *args)
{
	int	i;

	i = 0;
	while (i < args->number_of_philosophers)
	{
		if (is_dead(args, &args->philos[i]))
		{
			pthread_mutex_lock(&args->dead_mutex);
			args->simulation_running = 0;
			pthread_mutex_unlock(&args->dead_mutex);
			print_status(&args->philos[i], DEAD);
			return (0);
		}
		i++;
	}
	return (1);
}
