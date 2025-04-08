# include "philo_bonus.h"

void	ft_usleep(long int time_in_ms)
{
	long int	start_time;

	start_time = 0;
	start_time = get_timestamp();
	while ((get_timestamp() - start_time) < time_in_ms)
		usleep(1000);
}

void	write_state(char *str, t_phil *phil)
{
	int	cur_time;

	cur_time = get_timestamp() - phil->params->start_time;
	sem_wait(phil->params->sem_console);
	printf("%09d %d %s\n", cur_time, phil->pos, str);
	sem_post(phil->params->sem_console);
}

long	get_timestamp(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}
