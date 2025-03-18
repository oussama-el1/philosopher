/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-hadr <oel-hadr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 16:01:26 by oel-hadr          #+#    #+#             */
/*   Updated: 2025/03/18 11:06:16 by oel-hadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	set_args_helper(t_philo_args *args, int ac, char **av)
{
	if (args->time_to_die <= 0 || args->time_to_eat <= 0
		|| args->time_to_sleep <= 0)
	{
		printf("Error: Time values not valid.\n");
		return (-1);
	}
	if (ac == 6)
	{
		args->min_must_eat = ft_atoi(av[5]);
		if (args->min_must_eat <= 0)
		{
			printf("Error: Minimum meals not valid.\n");
			return (-1);
		}
	}
	else
		args->min_must_eat = -1;
	args->simulation_running = 1;
	args->philos = NULL;
	return (1);
}

int	set_args(t_philo_args *args, int ac, char **av)
{
	if (!is_valid_number(av[1]) || !is_valid_number(av[2])
		|| !is_valid_number(av[3]) || !is_valid_number(av[4])
		|| (ac == 6 && !is_valid_number(av[5])))
		return (-1);
	args->number_of_philosophers = ft_atoi(av[1]);
	if (args->number_of_philosophers <= 0)
	{
		printf("Error: Number of philosophers not valid.\n");
		return (-1);
	}
	args->number_forks = args->number_of_philosophers;
	args->time_to_die = ft_atoi(av[2]);
	args->time_to_eat = ft_atoi(av[3]);
	args->time_to_sleep = ft_atoi(av[4]);
	args->philos = NULL;
	return (set_args_helper(args, ac, av));
}

int	main(int ac, char **av)
{
	t_philo_args	args;

	if (ac != 5 && ac != 6)
	{
		printf("Usage: ./philo number_of_philosophers");
		printf(" time_to_die time_to_eat time_to_sleep [min_must_eat]\n");
		return (1);
	}
	if (set_args(&args, ac, av) < 0)
	{
		printf("Invalid arguments provided.\n");
		return (1);
	}
	init_semaphores(&args);
	init_philos(&args);
	create_process(&args);
	cleanup(NULL, &args);
	return (0);
}
