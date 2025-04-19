/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-hadr <oel-hadr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 19:21:47 by oel-hadr          #+#    #+#             */
/*   Updated: 2025/04/17 14:46:22 by oel-hadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_status(t_philo *philo, int status)
{
	long int	time;
	int			running;

	pthread_mutex_lock(&philo->args->print_mutex);
	time = get_time() - philo->args->start_time;
	if (status == DEAD)
	{
		printf("%ld %d died\n", time, philo->id);
		pthread_mutex_unlock(&philo->args->print_mutex);
		return ;
	}
	running = 1;
	set_running_status(&running, philo);
	if (!running)
		return (pthread_mutex_unlock(&philo->args->print_mutex), (void)0);
	else if (status == TAKE_FORK)
		printf("%ld %d has taken a fork\n", time, philo->id);
	else if (status == EAT)
		printf("%ld %d is eating\n", time, philo->id);
	else if (status == SLEEP)
		printf("%ld %d is sleeping\n", time, philo->id);
	else if (status == THINK)
		printf("%ld %d is thinking\n", time, philo->id);
	pthread_mutex_unlock(&philo->args->print_mutex);
}

int	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	pick_up_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->left_fork->mutex);
	print_status(philo, TAKE_FORK);
	pthread_mutex_lock(&philo->right_fork->mutex);
	print_status(philo, TAKE_FORK);
}

void	put_down_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->left_fork->mutex);
	pthread_mutex_unlock(&philo->right_fork->mutex);
}

void	ft_usleep(int msecond)
{
	int	now;

	now = get_time();
	while (get_time() - now < msecond)
		usleep(500);
}
