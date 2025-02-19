/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-hadr <oel-hadr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 19:06:40 by oel-hadr          #+#    #+#             */
/*   Updated: 2025/02/19 19:28:12 by oel-hadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philosopher_routine(void *arg)
{
	t_philo *philo = (t_philo *)arg;
	t_philo_args *args = philo->args;

	while (args->simulation_running)
	{
		think(philo);
		eat(philo);
		sleep_philo(philo);

		if (args->min_must_eat > 0 && philo->meals_eaten >= args->min_must_eat)
			break;
	}
	return NULL;
}

void	*monitor_routine(void *arg)
{
	int	i;
    t_philo_args *args = (t_philo_args *)arg;
    
    while (1)
    {
		i = 0;
        while (i < args->number_of_philosophers)
        {
            pthread_mutex_lock(&args->print_mutex);
            if (get_time() - args->philos[i].last_meal_time > args->time_to_die)
            {
                print_status(&args->philos[i], "died");
                args->simulation_running = 0;
                pthread_mutex_unlock(&args->print_mutex);
                return NULL;
            }
            pthread_mutex_unlock(&args->print_mutex);
			i++;
        }
        usleep(1000);
    }
    return NULL;
}

