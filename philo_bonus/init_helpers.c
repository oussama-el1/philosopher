/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_helpers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-hadr <oel-hadr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 17:32:24 by oel-hadr          #+#    #+#             */
/*   Updated: 2025/03/18 11:27:10 by oel-hadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	init_semaphores(t_philo_args *args)
{
	args->forks = sem_open("/forks", O_CREAT, 0644, args->number_of_philosophers);
	args->print_sem = sem_open("/print", O_CREAT, 0644, 1);
	args->dead_sem = sem_open("/dead", O_CREAT, 0644, 1);
	args->meal_sem = sem_open("/meal", O_CREAT, 0644, 1);
	printf("forks: %p\n", args->forks);
	printf("print: %p\n", args->print_sem);
	printf("dead: %p\n", args->dead_sem);
	printf("meal: %p\n", args->meal_sem);
	if (args->forks == SEM_FAILED || args->print_sem == SEM_FAILED || args->dead_sem == SEM_FAILED || args->meal_sem == SEM_FAILED)
	{
		cleanup("Error creating semaphores", args);
		return (-1);
	}
	return (1);
}

int	wait_for_childs(t_philo_args *args)
{
	int	i;

	i = 0;
	while (i < args->number_of_philosophers)
	{
		if (waitpid(args->philos[i].pid, NULL, 0) == -1)
		{
			cleanup("Error wait for process", args);
			return (-1);
		}
		i++;
	}
	return (1);
}

int	monitor_handler(t_philo_args *args)
{
	pid_t	monitor_pid;

	monitor_pid = fork();
	if (monitor_pid < 0)
	{
		cleanup("Error forking Process", args);
		return (-1);
	}
	else if (monitor_pid == 0)
	{
		// monitor_routine();
		exit(0);	
	}
	if (waitpid(monitor_pid, NULL, 0) == -1)
		return (-1);
	return (1);
}

int	create_process(t_philo_args *args)
{
	int		i;
	pid_t	pid;
	pid_t	monitor_pid;

	i = 0;
	while (i < args->number_of_philosophers)
	{
		pid = fork();
		args->philos[i].born_at = get_time();
		if (pid == 0)
		{
			philosopher_routine(&args->philos[i]);
			exit(0);
		}
		else if (pid < -1)
		{
			cleanup("Error forking Process", args);
			return (-1);
		}
		args->philos[i].pid = pid;
		i++;
	}
	monitor_pid = fork();
	return (wait_for_childs(args));
}

int	init_philos(t_philo_args *args)
{
	int	i;

	args->philos = (t_philo *)malloc(sizeof(t_philo) * args->number_of_philosophers);
	if (!args->philos)
	{
		cleanup("Error allocating memmory", args);
		return (-1);
	}
	i = 0;
	while (i < args->number_of_philosophers)
	{
		args->philos[i].args = args;
		args->philos[i].id = i + 1;
		args->philos[i].meals_eaten = 0;
		args->philos[i].last_meal_time = get_time();
		i++;
	}
	return (1);
}
