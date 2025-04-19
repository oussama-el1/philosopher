/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_helpers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-hadr <oel-hadr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 20:21:12 by oel-hadr          #+#    #+#             */
/*   Updated: 2025/04/14 11:32:04 by oel-hadr         ###   ########.fr       */
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

void	eat(t_philo *philo)
{
	pick_up_forks(philo);
	print_status(philo, "is eating");
	ft_usleep(philo->args->time_to_eat);
	sem_wait(philo->last_meal);
	philo->last_meal_time = get_time();
	philo->meals_eaten++;
	sem_post(philo->last_meal);
	sem_post(philo->args->forks);
	sem_post(philo->args->forks);
}

void	wait_philos(t_philo_args *args)
{
	int	i;

	i = 0;
	while (i < args->number_of_philosophers)
	{
		if (waitpid(args->philos[i].pid, NULL, 0) == -1)
			break ;
		i++;
	}
}
