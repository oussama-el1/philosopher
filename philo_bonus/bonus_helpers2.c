/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_helpers2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oussama <oussama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 17:49:38 by oel-hadr          #+#    #+#             */
/*   Updated: 2025/03/30 21:57:32 by oussama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

long int	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	ft_usleep(int msecond)
{
	long int	now;

	now = get_time();
	while (get_time() - now < msecond)
		usleep(500);
}

void	set_running_status(int *running, t_philo *philo)
{
	sem_wait(philo->args->dead_sem);
	*running = philo->args->simulation_running;
	sem_post(philo->args->dead_sem);
}

void	print_status(t_philo *philo, char *status)
{
	int	running;

	set_running_status(&running, philo);
	if (!running)
		return ;
	sem_wait(philo->args->print_sem);
	printf("%ld %d %s\n", get_time() - philo->born_at, philo->id, status);
	sem_post(philo->args->print_sem);
}

void	cleanup(char *message, t_philo_args *args)
{
	if (message)
	{
		write(2, message, ft_strlen(message));
		write(2, "\n", 1);
	}
	sem_close(args->dead_sem);
	sem_unlink("/dead");
	sem_close(args->print_sem);
	sem_unlink("/print");
	sem_close(args->forks);
	sem_unlink("/forks");
	free(args->philos);
	if (message)
		exit(1);
}
