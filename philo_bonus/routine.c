/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-hadr <oel-hadr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 20:08:04 by oel-hadr          #+#    #+#             */
/*   Updated: 2025/04/14 11:57:20 by oel-hadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*monitor_philos(void *arg)
{
	t_philo_args	*args;
	t_philo			*philos;
	int				i;

	philos = (t_philo *)arg;
	args = (*philos).args;
	sem_wait(args->dead_sem);
	i = 0;
	while (i < args->number_of_philosophers)
	{
		kill(philos[i].pid, SIGTERM);
		i++;
	}
	return (NULL);
}

void	*monitor_death(void *arg)
{
	t_philo_args	*args;
	t_philo			*philo;
	long			time;

	philo = (t_philo *)arg;
	args = philo->args;
	while (1)
	{
		sem_wait(philo->last_meal);
		time = get_time() - philo->last_meal_time;
		if (time > args->time_to_die)
		{
			sem_post(philo->last_meal);
			sem_wait(args->print_sem);
			printf("%ld %d died\n", get_time() - philo->born_at, philo->id);
			sem_post(args->dead_sem);
			return (NULL);
		}
		sem_post(philo->last_meal);
	}
	return (NULL);
}

void	philosopher_routine(t_philo *philo)
{
	pthread_t	monitor_dead;

	philo->born_at = get_time();
	if (pthread_create(&monitor_dead, NULL, monitor_death, philo) != 0)
		cleanup("Error creating monitor thread", philo->args, 0);
	if (pthread_detach(monitor_dead) != 0)
		cleanup("Error detaching monitor thread", philo->args, 0);
	if (philo->id % 2 != 0)
		ft_usleep(philo->args->time_to_eat / 2);
	while (1)
	{
		sem_wait(philo->last_meal);
		if (philo->meals_eaten >= philo->args->min_must_eat
			&& philo->args->min_must_eat != -1)
		{
			sem_post(philo->last_meal);
			break ;
		}
		sem_post(philo->last_meal);
		eat(philo);
		print_status(philo, "is sleeping");
		ft_usleep(philo->args->time_to_sleep);
		print_status(philo, "is thinking");
	}
	sem_post(philo->args->dead_sem);
}
