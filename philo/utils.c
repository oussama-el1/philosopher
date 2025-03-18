/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-hadr <oel-hadr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 17:55:36 by oel-hadr          #+#    #+#             */
/*   Updated: 2025/02/25 15:17:22 by oel-hadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	cleanup(t_philo_args *args, char *message)
{
	int	i;

	i = 0;
	if (message)
		write(2, message, ft_strlen(message));
	while (i < args->number_of_philosophers)
	{
		pthread_mutex_destroy(&args->forks[i].mutex);
		i++;
	}
	pthread_mutex_destroy(&args->print_mutex);
	pthread_mutex_destroy(&args->meal_mutex);
	pthread_mutex_destroy(&args->dead_mutex);
	free(args->philos);
	free(args->forks);
}
