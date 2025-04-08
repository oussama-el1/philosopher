/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oussama <oussama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 20:08:04 by oel-hadr          #+#    #+#             */
/*   Updated: 2025/04/09 00:15:10 by oussama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*philosopher_routine(void *arg)
{
	pthread_t	death_thread;
	t_philo		*philo;

	philo = (t_philo *)arg;
	pthread_create(&death_thread, NULL, monitor_routine, philo);
	if (philo
		ft_usleep(philO->params->time_to_eat);
	while (1)
	{
		if (philO->meal_count >= philO->params->meal_max
			&& philO->params->meal_max > 0)
			break ;
		take_fork(philO);
		take_fork(philO);
		write_state("is eating", philO);
		ft_usleep(philO->params->time_to_eat);
		philO->meal_count++;
		sem_wait(philO->sem_last_meal);
		philO->last_meal = get_timestamp() - philO->params->start_time;
		sem_post(philO->sem_last_meal);
		release_forks_and_sleep(philO);
		ft_usleep((philO->params->time_to_die - philO->params->time_to_eat
				- philO->params->time_to_sleep) / 2);
	}
	sem_post(phil->params->finished);
	return (1);
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
