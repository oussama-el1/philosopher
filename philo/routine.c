/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-hadr <oel-hadr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 19:06:40 by oel-hadr          #+#    #+#             */
/*   Updated: 2025/04/17 18:58:28 by oel-hadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*one_philo_case(t_philo *philo)
{
	pthread_mutex_lock(&philo->left_fork->mutex);
	print_status(philo, TAKE_FORK);
	ft_usleep(philo->args->time_to_die);
	pthread_mutex_unlock(&philo->left_fork->mutex);
	return (NULL);
}

int	check_eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->args->meal_mutex);
	if (philo->args->min_must_eat != -1
		&& philo->meals_eaten >= philo->args->min_must_eat)
	{
		pthread_mutex_unlock(&philo->args->meal_mutex);
		return (0);
	}
	pthread_mutex_unlock(&philo->args->meal_mutex);
	return (1);
}

void	*philosopher_routine(void *arg)
{
	t_philo			*philo;
	int				running;

	philo = (t_philo *)arg;
	if (philo->args->number_of_philosophers == 1)
		return (one_philo_case(philo));
	if (philo->id % 2 == 1)
		ft_usleep(philo->args->time_to_eat / 2);
	while (1)
	{
		if (!check_eating(philo))
			break ;
		eat(philo);
		set_running_status(&running, philo);
		if (!running)
			break ;
		print_status(philo, SLEEP);
		ft_usleep(philo->args->time_to_sleep);
		set_running_status(&running, philo);
		if (!running)
			break ;
		print_status(philo, THINK);
	}
	return (NULL);
}

void	*monitor_routine(void *arg)
{
	t_philo_args	*args;

	args = (t_philo_args *)arg;
	while (1)
	{
		if (!is_all_alive(args) || is_all_full(args))
			break ;
	}
	return (NULL);
}
