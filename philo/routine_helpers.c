/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_helpers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-hadr <oel-hadr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 19:10:04 by oel-hadr          #+#    #+#             */
/*   Updated: 2025/02/20 16:30:37 by oel-hadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


void	think(t_philo *philo)
{
	print_status(philo, "is thinking");
	usleep(1000);
}

void	eat(t_philo *philo)
{
	pick_up_forks(philo);
	pthread_mutex_lock(&philo->args->meal_mutex);
	philo->last_meal_time = get_time();
	pthread_mutex_unlock(&philo->args->meal_mutex);
	philo->meals_eaten++;
	print_status(philo, "is eating");
	usleep(philo->args->time_to_eat * 1000);
	put_down_forks(philo);
}

void	sleep_philo(t_philo *philo)
{
	print_status(philo, "is sleeping");
	usleep(philo->args->time_to_sleep * 1000);
}

