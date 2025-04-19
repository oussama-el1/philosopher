/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_helpers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-hadr <oel-hadr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 17:32:24 by oel-hadr          #+#    #+#             */
/*   Updated: 2025/04/14 11:30:57 by oel-hadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	init_semaphores(t_philo_args *args)
{
	sem_unlink("/print");
	sem_unlink("/forks");
	sem_unlink("/dead");
	args->forks = sem_open("/forks", O_CREAT,
			0644, args->number_of_philosophers);
	args->print_sem = sem_open("/print", O_CREAT, 0644, 1);
	args->dead_sem = sem_open("/dead", O_CREAT, 0644, 1);
	if (args->forks == SEM_FAILED || args->print_sem == SEM_FAILED
		|| args->dead_sem == SEM_FAILED)
		cleanup("Error creating semaphores", args, 0);
	sem_wait(args->dead_sem);
}

static void	init_one(t_philo_args *args, int i)
{
	char	*sem_name;

	args->philos[i].args = args;
	args->philos[i].id = i + 1;
	args->philos[i].meals_eaten = 0;
	args->philos[i].last_meal_time = get_time();
	sem_name = ft_itoa(i + 1);
	if (!sem_name)
		cleanup("Error allocating memory", args, 0);
	sem_unlink(sem_name);
	args->philos[i].last_meal = sem_open(sem_name, O_CREAT, 0644, 1);
	sem_unlink(sem_name);
	if (args->philos[i].last_meal == SEM_FAILED)
	{
		free(sem_name);
		cleanup("Error creating semaphore", args, 0);
	}
	free(sem_name);
}

void	init_philos(t_philo_args *args)
{
	int	i;

	args->philos = (t_philo *)malloc(sizeof(t_philo)
			* args->number_of_philosophers);
	if (!args->philos)
		cleanup("Error allocating memmory", args, 0);
	i = 0;
	while (i < args->number_of_philosophers)
	{
		init_one(args, i);
		i++;
	}
}

void	create_process(t_philo_args *args)
{
	t_philo	*philos;
	int		i;

	i = 0;
	while (i < args->number_of_philosophers)
	{
		args->philos[i].pid = fork();
		if (args->philos[i].pid == -1)
			cleanup("Error forking Process", args, 0);
		else if (args->philos[i].pid == 0)
			return (philosopher_routine(&args->philos[i]), (void)0);
		i++;
	}
	philos = args->philos;
	if (pthread_create(&args->monitor_thread, NULL,
			monitor_philos, philos) != 0)
		cleanup("Error creating monitor thread", args, 1);
	if (pthread_detach(args->monitor_thread) != 0)
		cleanup("Error detaching monitor thread", args, 1);
}
