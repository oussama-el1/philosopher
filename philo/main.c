/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-hadr <oel-hadr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 17:16:20 by oel-hadr          #+#    #+#             */
/*   Updated: 2025/02/19 19:03:21 by oel-hadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int set_args(t_philo_args *args, int ac, char **av)
{
	if (!is_valid_number(av[1]) || !is_valid_number(av[2]) ||
		!is_valid_number(av[3]) || !is_valid_number(av[4]) ||
		(ac == 6 && !is_valid_number(av[5])))
		return (-1);
	
	args->number_of_philosophers = ft_atoi(av[1]);
	if (args->number_of_philosophers <= 0)
	{
		printf("Error: Number of philosophers must be greater than 0.\n");
		return (-1);
	}
	args->number_forks = args->number_of_philosophers;
	args->time_to_die = ft_atoi(av[2]);
	args->time_to_eat = ft_atoi(av[3]);
	args->time_to_sleep = ft_atoi(av[4]);

	if (args->time_to_die <= 0 || args->time_to_eat <= 0 || args->time_to_sleep <= 0)
	{
		printf("Error: Time values must be greater than 0.\n");
		return (-1);
	}
	if (ac == 6)
	{
		args->min_must_eat = ft_atoi(av[5]);
		if (args->min_must_eat <= 0)
		{
			printf("Error: Minimum meals must be greater than 0.\n");
			return (-1);
		}
	}
	else
		args->min_must_eat = -1;

	return (1);
}

int main(int ac, char **av)
{
	t_philo_args	args;

	if (ac != 5 && ac != 6)
	{
		printf("Usage: ./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [min_must_eat]\n");
		return (1);
	}
	if (set_args(&args, ac, av) == -1)
	{
		printf("Invalid arguments provided.\n");
		return (1);
	}
    if (init_philos(&args) == -1)
    {
        printf("Error : init philos\n");
        return (1);
    }
	return (0);
}
