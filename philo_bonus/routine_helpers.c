/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_helpers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-hadr <oel-hadr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 20:21:12 by oel-hadr          #+#    #+#             */
/*   Updated: 2025/02/26 20:37:36 by oel-hadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	pick_up_forks(t_philo *philo)
{
	sem_wait(philo->args->forks);
	print_status(philo, "has taken a fork");
	sem_wait(philo->args->forks);
	print_status(philo, "has taken a fork");
}

void	put_down_forks(t_philo *philo)
{
	sem_post(philo->args->forks);
	sem_post(philo->args->forks);
}

void	eat(t_philo *philo)
{
	pick_up_forks(philo);
	philo->last_meal_time = get_time();
	philo->meals_eaten++;
	print_status(philo, "is eating");
	ft_usleep(philo->args->time_to_eat);
	put_down_forks(philo);
}

int	is_dead(t_philo_args *args, t_philo *philo)
{
	int	dead;

	// pthread_mutex_lock(&args->meal_mutex);
	dead = (get_time() - philo->last_meal_time > args->time_to_die);
	// pthread_mutex_unlock(&args->meal_mutex);
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
			print_status(&args->philos[i], "died");
			sem_wait(args->dead_sem);
			args->simulation_running = 0;
			sem_post(args->dead_sem);
			return (0);
		}
		i++;
	}
	return (1);
}

int	is_all_full(t_philo_args *args)
{
	int	i;

	i = 0;
	while (i < args->number_of_philosophers)
	{
		if (args->min_must_eat < 0
			|| args->philos[i].meals_eaten < args->min_must_eat)
			return (0);
		i++;
	}
	sem_wait(args->dead_sem);
	args->simulation_running = 0;
	sem_post(args->dead_sem);
	return (1);
}
