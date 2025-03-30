/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oussama <oussama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 16:01:44 by oel-hadr          #+#    #+#             */
/*   Updated: 2025/03/30 20:53:12 by oussama          ###   ########.fr       */
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
# include <fcntl.h>
# include <semaphore.h>
# include <sys/stat.h>
# include <sys/wait.h>

struct	s_philo_args;

typedef struct s_philo
{
	int					id;
	pid_t				pid;
	int					meals_eaten;
	int					born_at;
	int					last_meal_time;
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
	int				simulation_running;
	t_philo			*philos;
	sem_t			*forks;
	sem_t			*print_sem;
	sem_t			*dead_sem;
	sem_t			*meal_sem;
}	t_philo_args;

int		ft_atoi(const char *str);
int		is_valid_number(const char *str);
int		ft_strlen(char *s);
int		get_time(void);
void	set_running_status(int *running, t_philo *philo);
void	print_status(t_philo *philo, char *status);
void	ft_usleep(int msecond);
void	cleanup(char *message, t_philo_args *args);


// init functions
int		init_semaphores(t_philo_args *args);
int		init_philos(t_philo_args *args);
int		create_process(t_philo_args *args);

// routines
void	pick_up_forks(t_philo *philo);
void	put_down_forks(t_philo *philo);
int		is_all_full(t_philo_args *args);
int		is_dead(t_philo_args *args, t_philo *philo);
int		is_all_alive(t_philo_args *args);
void	eat(t_philo *philo);
void	*philosopher_routine(void *arg);
void	*monitor_routine(void *arg);


#endif
