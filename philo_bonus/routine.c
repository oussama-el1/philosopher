/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oussama <oussama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 20:08:04 by oel-hadr          #+#    #+#             */
/*   Updated: 2025/03/30 20:56:07 by oussama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*one_philo_case(t_philo *philo)
{
	sem_wait(philo->args->forks);
	print_status(philo, "has taken a fork");
	ft_usleep(philo->args->time_to_die);
	sem_post(philo->args->forks);
	return (NULL);
}

void	*philosopher_routine(void *arg)
{
	t_philo			*philo;
	int				running;

	philo = (t_philo *)arg;
	if (philo->args->number_of_philosophers == 1)
		return (one_philo_case(philo));
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
