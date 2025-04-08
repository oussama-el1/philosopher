/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oussama <oussama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 19:06:40 by oel-hadr          #+#    #+#             */
/*   Updated: 2025/03/30 22:11:39 by oussama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*one_philo_case(t_philo *philo)
{
	pthread_mutex_lock(&philo->left_fork->mutex);
	print_status(philo, "has taken a fork");
	ft_usleep(philo->args->time_to_die);
	pthread_mutex_unlock(&philo->left_fork->mutex);
	return (NULL);
}

void	*philosopher_routine(void *arg)
{
	t_philo			*philo;
	int				running;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 1)
		ft_usleep(1);
	while (1)
	{
		set_running_status(&running, philo);
		eat(philo);
		set_running_status(&running, philo);
		if (!running)
			break ;
		print_status(philo, "is sleeping");
		ft_usleep(philo->args->time_to_sleep);
		set_running_status(&running, philo);
		if (!running)
			break ;
		print_status(philo, "is thinking");
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
