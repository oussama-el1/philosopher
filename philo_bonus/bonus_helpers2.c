/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_helpers2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-hadr <oel-hadr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 17:49:38 by oel-hadr          #+#    #+#             */
/*   Updated: 2025/04/17 16:36:51 by oel-hadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	ft_usleep(long int msecond)
{
	long	now;

	now = get_time();
	while (get_time() - now < msecond)
		usleep(500);
}

void	print_status(t_philo *philo, char *status)
{
	sem_wait(philo->args->print_sem);
	printf("%ld %d %s\n", get_time() - philo->born_at,
		philo->id, status);
	sem_post(philo->args->print_sem);
}

void	close_semaphores(t_philo_args *args)
{
	int	i;

	i = 0;
	sem_close(args->dead_sem);
	sem_close(args->print_sem);
	sem_close(args->forks);
	if (args->philos)
	{
		while (i < args->number_of_philosophers)
		{
			if (args->philos[i].last_meal)
				sem_close(args->philos[i].last_meal);
			i++;
		}
	}
	sem_unlink("/print");
	sem_unlink("/forks");
	sem_unlink("/dead");
}

void	cleanup(char *message, t_philo_args *args, int kill_flag)
{
	int	i;

	i = 0;
	if (message)
		write(2, message, ft_strlen(message));
	close_semaphores(args);
	if (kill_flag)
	{
		while (i < args->number_of_philosophers)
		{
			if (args->philos[i].pid > 0)
				kill(args->philos[i].pid, SIGTERM);
			i++;
		}
	}
	free(args->philos);
	if (message)
		exit(1);
}
