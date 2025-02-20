/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-hadr <oel-hadr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 19:21:47 by oel-hadr          #+#    #+#             */
/*   Updated: 2025/02/20 16:12:51 by oel-hadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_status(t_philo *philo, char *status)
{
	pthread_mutex_lock(&philo->args->print_mutex);
	printf("%lld %d %s\n", get_time() - philo->born_at, philo->id, status);
	pthread_mutex_unlock(&philo->args->print_mutex);
}

long long	get_time(void)
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000LL + tv.tv_usec / 1000);
}

void pick_up_forks(t_philo *philo)
{
    if (philo->id % 2 == 0)
    {
        pthread_mutex_lock(&philo->right_fork->mutex);
        print_status(philo, "has taken a fork");
        pthread_mutex_lock(&philo->left_fork->mutex);
        print_status(philo, "has taken a fork");
    }
    else
    {
        pthread_mutex_lock(&philo->left_fork->mutex);
        print_status(philo, "has taken a fork");
        pthread_mutex_lock(&philo->right_fork->mutex);
        print_status(philo, "has taken a fork");
    }
}


void	put_down_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->left_fork->mutex);
	pthread_mutex_unlock(&philo->right_fork->mutex);
}
