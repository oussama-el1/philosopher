/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-hadr <oel-hadr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 16:01:44 by oel-hadr          #+#    #+#             */
/*   Updated: 2025/04/12 22:16:31 by oel-hadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdlib.h>
# include <stdio.h>
# include <limits.h>
# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>
# include <semaphore.h>
# include <signal.h>

struct	s_philo_args;

typedef struct s_philo
{
	int					id;
	pid_t				pid;
	int					meals_eaten;
	long				born_at;
	long				last_meal_time;
	pthread_t			monitor;
	sem_t				*last_meal;
	struct s_philo_args	*args;
}	t_philo;

typedef struct s_philo_args
{
	int				number_of_philosophers;
	int				number_forks;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				min_must_eat;
	t_philo			*philos;
	sem_t			*forks;
	sem_t			*print_sem;
	sem_t			*dead_sem;
	pthread_t		monitor_thread;
}	t_philo_args;

// libft helpers
int		ft_atoi(const char *str);
char	*ft_itoa(int n);
int		ft_strlen(char *s);

// project helpers
int		is_valid_number(const char *str);
long	get_time(void);
void	print_status(t_philo *philo, char *status);
void	ft_usleep(long int msecond);
void	cleanup(char *message, t_philo_args *args, int kill_flag);

// init functions
void	init_semaphores(t_philo_args *args);
void	init_philos(t_philo_args *args);

// process management
void	create_process(t_philo_args *args);
void	wait_philos(t_philo_args *args);

// routines
void	pick_up_forks(t_philo *philo);
void	put_down_forks(t_philo *philo);
void	eat(t_philo *philo);
void	philosopher_routine(t_philo *philo);
void	*monitor_philos(void *arg);

#endif
