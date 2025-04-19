/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-hadr <oel-hadr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 17:55:36 by oel-hadr          #+#    #+#             */
/*   Updated: 2025/04/16 16:38:09 by oel-hadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	cleanup(t_philo_args *args, char *message, int destroy, int forks)
{
	int	i;

	i = 0;
	if (message)
		write(2, message, ft_strlen(message));
	while (i < forks)
	{
		pthread_mutex_destroy(&args->forks[i].mutex);
		i++;
	}
	if (destroy)
	{
		pthread_mutex_destroy(&args->print_mutex);
		pthread_mutex_destroy(&args->meal_mutex);
		pthread_mutex_destroy(&args->dead_mutex);
	}
	free(args->philos);
	free(args->forks);
}
