/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-hadr <oel-hadr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 15:54:09 by oel-hadr          #+#    #+#             */
/*   Updated: 2025/04/17 13:30:40 by oel-hadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <stdio.h>
# include <limits.h>
# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>

# define DEAD 0
# define TAKE_FORK 1
# define EAT 2
# define SLEEP 3
# define THINK 4

typedef struct s_fork
{
	pthread_mutex_t	mutex;
}	t_fork;

struct	s_philo_args;

typedef struct s_philo
{
	int					id;
	pthread_t			thread;
	int					meals_eaten;
	int					last_meal_time;
	t_fork				*left_fork;
	t_fork				*right_fork;
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
	int				start_time;
	t_philo			*philos;
	t_fork			*forks;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	meal_mutex;
	pthread_mutex_t	dead_mutex;
}	t_philo_args;

// helpers
int			ft_atoi(const char *str);
int			is_valid_number(const char *str);
void		print_status(t_philo *philo, int status);
int			get_time(void);
void		pick_up_forks(t_philo *philo);
void		put_down_forks(t_philo *philo);
void		cleanup(t_philo_args *args, char *message, int destroy, int forks);
int			ft_strlen(char *s);
void		set_running_status(int *running, t_philo *philo);

// init function
int			init_philos(t_philo_args *args);
void		init_threads(t_philo_args *args);

// routine
void		*philosopher_routine(void *arg);
void		*monitor_routine(void *arg);
void		think(t_philo *philo);
void		eat(t_philo *philo);
void		sleep_philo(t_philo *philo);
void		ft_usleep(int msc);
int			is_all_full(t_philo_args *args);
int			is_dead(t_philo_args *args, t_philo *philo);
int			is_all_alive(t_philo_args *args);

#endif
