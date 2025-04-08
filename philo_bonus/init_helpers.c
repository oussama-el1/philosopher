/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_helpers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oussama <oussama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 17:32:24 by oel-hadr          #+#    #+#             */
/*   Updated: 2025/04/08 23:48:54 by oussama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	init_semaphores(t_philo_args *args)
{
	args->forks = sem_open("/forks", O_CREAT, 0644, args->number_of_philosophers);
	args->print_sem = sem_open("/print", O_CREAT, 0644, 1);
	args->dead_sem = sem_open("/dead", O_CREAT, 0644, 1);
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
		monitor_routine(args);
		exit(0);
	}
	if (waitpid(monitor_pid, NULL, 0) == -1)
		return (-1);
	return (1);
}

void	create_process(t_philo_args *args)
{
	int		i;
	pid_t	pid;

	i = 0;
	while (i < args->number_of_philosophers)
	{
		args->philos[i].pid = fork();
		if (args->philos[i].pid == 0)
			return (philosopher_routine(&args->philos[i]));
		else if (args->philos[i].pid < 0)
			cleanup("Error creating process", args);
	}
	if (pthread_create(&(args->monitor_thread), NULL,
		monitor_routine, args->philos) != 0)
		cleanup("Error creating monitor thread", args);
}

void init_philos_helper(t_philo_args *args, int i)
{
	char	*sem_name;

	args->philos[i].id = i + 1;
	args->philos[i].meals_eaten = 0;
	args->philos[i].last_meal_time = 0;
	args->philos[i].args = args;
	sem_name = ft_itoa(i + 1);
	if (!sem_name)
		cleanup("Error allocating memory", args);
	args->philos[i].meal_sem = sem_open(sem_name, O_CREAT, 0644, 1);
	if (args->philos[i].meal_sem == SEM_FAILED)
	{
		free(sem_name);
		cleanup("Error creating semaphores", args);
	}
	free(sem_name);
}

int	init_philos(t_philo_args *args)
{
	int	i;
	char *sem_name;

	args->philos = (t_philo *)malloc(sizeof(t_philo) * args->number_of_philosophers);
	if (!args->philos)
	{
		cleanup("Error allocating memmory", args);
		return (-1);
	}
	i = 0;
	while (i < args->number_of_philosophers)
	{
		init_philos_helper(args, i);
		i++;
	}
	return (1);
}
